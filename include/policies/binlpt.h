#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

namespace MOGSLib { namespace Policy {

/**
 *  @brief A workload-aware policy that packs adjacent tasks together and distribute them in a greedy fashion.
 *  @tparam L A load data type definition.
 */
template<typename L>
class BinLPT {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;
  using Load = L;

  struct Chunk {
    std::pair<Index, Index> range;
    Load load;
    
    Chunk() {}
    Chunk(const Index &f, const Index &la, const Load &l) : range(std::make_pair(f,la)), load(l) {}

    bool operator >(const Chunk &o) const { return load > o.load; }
  };

  struct PU {
    Index id;
    Load load;
    
    PU(const Index &i, const Load &l) : id(i), load(l) {}
    bool operator <(const PU &o) const { return load < o.load; }
  };

  static std::vector<Chunk> create_chunks(const std::vector<Load> &tasks, const Index &n) {
    std::vector<Chunk> chunks;
    
    if(tasks.empty())
      return chunks;

    std::vector<Load> partial_workload = std::vector<Load>(tasks.size()+1);
    partial_workload[0] = 0; // First element is 0
    std::partial_sum(tasks.begin(), tasks.end(), partial_workload.begin()+1); // Last element is the total workload.

    auto average_weight = partial_workload.back()/n; // average size per chunk.

    Index begin = 0;
    while(chunks.size() < n) {
      auto end = begin;
      for(++end; end < partial_workload.size()-1; ++end) // Not interested in the last element, which is the total workload.
          if(partial_workload[end] - partial_workload[begin] >= average_weight)
            break;

      chunks.push_back(Chunk(begin, end, partial_workload[end] - partial_workload[begin]));
      begin = end;
    }

    return chunks;
  }

  static inline std::vector<PU> create_pus(const std::vector<Load> &loads) {
    std::vector<PU> pus;
    Index i = 0;

    std::transform(loads.begin(), loads.end(), pus.begin(), [&i](const Load &l) { return PU(++i,l);});

    return pus;
  }

  static void map(TaskMap &map, const std::vector<Load> &task_loads, const std::vector<Load> &pu_loads, const Index &nchunks) {
    auto chunks = create_chunks(task_loads, nchunks);
    auto pus = create_pus(pu_loads);

    /* Organize the chunks in decreasing order */
    std::sort(chunks.begin(), chunks.end(), std::greater<Chunk>());

    /* Iterate over the chunks, starting from the largest, and assign them to PEs */
    for(auto chunk : chunks) {
      // Get the least overloaded PU.
      auto pu = *std::min_element(pus.begin(), pus.end());
      // Assign the task to the PU.
      for(auto i = std::get<0>(chunk.range); i < std::get<1>(chunk.range); ++i)
        map[i] = pu.id;
      // Update the load of the PU,
      pu.load += chunk.load;
    }
  }
};

}}