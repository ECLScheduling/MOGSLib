#pragma once

#include <dependencies/workload_aware.h>

#include <algorithm>
#include <numeric>

namespace MOGSLib { namespace Policy {

template<typename ... Deps>
class BinLPT;

/**
 *  @class BinLPT
 *  @brief A workload-aware policy that packs adjacent tasks together and distribute them in a greedy fashion.
 *  @tparam Id An index type to organize PUs and tasks.
 *  @tparam L The workload numeric type.
 */
template<typename I, typename L>
struct BinLPT<MOGSLib::Dependency::WorkloadAware<I,L>> {
  using Deps = MOGSLib::Dependency::WorkloadAware<I,L>;
  using Id = typename Deps::Id;
  using Load = typename Deps::Load;
  using Schedule = typename Deps::Schedule;

  /**
   *  @class Chunk
   *  @brief A chunk abstraction to wrap the range of task indices and the sum of their load.
   */
  struct Chunk {
    std::pair<Id, Id> range;
    Load load;
    
    Chunk() {}

    /**
     *  @brief A constructor that initialized all the necessary data.
     *  @param f The index of the first task associated with this chunk.
     *  @param la The index of the last task associated with this chunk.
     *  @param l The load of the chunk.
     */
    Chunk(const Id &f, const Id &la, const Load &l) : range(std::make_pair(f,la)), load(l) {}

    /**
     *  @brief Compares with another chunk by its load.
     */
    bool operator >(const Chunk &o) const { return load > o.load; }
  };

  /**
   *  @brief Creates the task chunks analyzing the workload of neighbour tasks (by id).
   *  @param tasks The task workloads.
   *  @param n The amount of chunks to be made
   */
  static std::vector<Chunk> create_chunks(const std::vector<Load> &tasks, const Id &n) {
    std::vector<Chunk> chunks;
    
    if(tasks.empty())
      return std::move(chunks);

    std::vector<Load> partial_workload = std::vector<Load>(tasks.size()+1);
    partial_workload[0] = 0; // First element is 0
    std::partial_sum(tasks.begin(), tasks.end(), partial_workload.begin()+1); // Last element is the total workload.

    std::cout << std::endl;

    auto average_weight = partial_workload.back()/n; // average size per chunk.

    Id begin = 0;
    while(chunks.size() < n-1) {
      auto end = begin;
      for(++end; end < partial_workload.size(); ++end) // Not interested in the last element, which is the total workload.
          if(partial_workload[end] - partial_workload[begin] >= average_weight)
            break;
      chunks.push_back(Chunk(begin, end, partial_workload[end] - partial_workload[begin]));
      begin = end;
    }

    // Get all the remainder tasks into one chunk.
    chunks.push_back(Chunk(begin, tasks.size(), partial_workload[tasks.size()] - partial_workload[begin]));

    return chunks;
  }

  /**
   *  @brief map The map of task-to-pu that will serve as the output.
   *  @param tasks A vector of task workloads.
   *  @param pus A vector of pu workloads.
   *  @param nchunks The number of chunks to be created.
   *
   *  BinLPT wraps tasks into chunks trying to balance the load of each chunk.
   *  It sorts the chunk array in decreasing order and iteratively assigns them to the most underloaded pu.
   */
  static void map(Schedule &map, const std::vector<Load> &tasks, std::vector<Load> &pus, const Id &nchunks) {
    auto chunks = create_chunks(tasks, nchunks);

    /* Organize the chunks in decreasing order */
    std::sort(chunks.begin(), chunks.end(), std::greater<Chunk>());

    /* Iterate over the chunks, starting from the largest, and assign them to PEs */
    for(auto chunk : chunks) {
      // Get the least overloaded PU.
      Id pu = 0;
      for(Id i = 1; i < pus.size(); ++i)
        if(pus[i] < pus[pu])
          pu = i;
      // Assign the task to the PU.
      for(auto i = std::get<0>(chunk.range); i < std::get<1>(chunk.range); ++i)
        map[i] = pu;
      // Update the load of the PU,
      pus[pu] += chunk.load;
    }
  }
};

}}