#pragma once

#include <dependencies/workload_aware.h>

namespace MOGSLib { namespace Policy {

/**
 * @brief A workload-aware policy that packs adjacent tasks together and distribute them in a greedy fashion.
 */
template<typename ... Deps>
class BinLPT {};

/**
 *  @class BinLPT
 *  @brief A workload-aware policy that packs adjacent tasks together and distribute them in a greedy fashion.
 *  @tparam Id An Id type to organize PUs and tasks.
 *  @tparam L The workload numeric type.
 */
template<typename I, typename L>
struct BinLPT<MOGSLib::Dependency::WorkloadAware<I,L>> {
  using Deps = MOGSLib::Dependency::WorkloadAware<I,L>;
  using Id = typename Deps::Id;
  using Load = typename Deps::Load;
  using Schedule = typename Deps::Schedule;

  /**
   * @brief Swap two values by reference
   **/
  template<typename T>
  static void swap(T &a, T &b) {
    const T t = a;
    a = b;
    b = t;
  }

  /**
   * @brief Structure to auxiliate the comparison in the sort algorithms
   **/
  template<typename T, bool decreasing_order>
  struct Compare {
    static bool value(T &a, T &b) {
      return a < b;
    }
  };

  /**
   * @brief Structure specialization to auxiliate the comparison in the sort algorithms.
   **/
  template<typename T>
  struct Compare<T, false> {
    static bool value(T &a, T &b) {
      return a > b;
    }
  };

  /**
   * @brief Insertion sort.
   *
   * @type T The type of elements to be sorted. Must perform < operator.
   * @type UInt The unsigned integer type to be used as the array Id.
   * @type decreasing_order A boolean to choose whether the algorithm should organize in ascending order or not. This value defaults to increasing order.
   *
   * @param map The original indices of the elements in a.
   * @param a The array of elements to be sorted.
   * @param n the size of the array a.
   **/
  template <typename T, typename UInt, bool decreasing_order = true>
  static void insertion_sort(UInt *map, T *a, const UInt n) {
    UInt i, j; /* Loop Ides.    */
    
    /* Sort. */
    for (i = 0; i < (n - 1); i++)
    {
      for (j = i + 1; j < n; j++)
      {
        /* Swap. */
        if (Compare<T, decreasing_order>::value(a[j], a[i]))
        {
          swap<T>(a[i], a[j]);
          swap<UInt>(map[i], map[j]);
        }
      }
    }
  }

  template<typename T>
  static T* compute_cummulativesum(const T* arr, const Id &size) {
    Id i;
    T *sum = new T[size]();

    for(i = 1; i < size; ++i)
      sum[i] = sum[i-1] + arr[i-1];
    return sum;
  }

  static Id* compute_chunksizes(const Id ntasks, const Load *workloads, const Id &nchunks) {
    Id i, cur_chunk;
    Id *chunksizes = new Id[nchunks]();
    Load *accum_workload, chunkweight;

    if(!ntasks)
      return chunksizes;

    accum_workload = compute_cummulativesum<Load>(workloads, ntasks);
    chunkweight = (accum_workload[ntasks - 1] + workloads[ntasks - 1])/nchunks; // average size per chunk.

    cur_chunk = 0;
    for(i = 0; i < ntasks; ++cur_chunk) {
      Id j = ntasks;

      if(cur_chunk < (nchunks - 1))
        for(j = i + 1; j < ntasks; ++j)
          if(accum_workload[j] - accum_workload[i] >= chunkweight)
            break;

      chunksizes[cur_chunk] = j - i;
      i = j;
    }

    delete [] accum_workload;
    return chunksizes;
  }

  static auto compute_chunkloads(const Load *workloads, const Id *chunksizes, const Id &k) {
    Id cur_chunk;
    Load *chunk_loads;

    chunk_loads = new Load[k]();

    cur_chunk = 0;
    for(Id i = 0; i < k; ++i)
      for(Id j = 0; j < chunksizes[i]; ++j)
        chunk_loads[i] += workloads[cur_chunk++];

    return chunk_loads;
  }

  static void map(Schedule &map, const Id &ntasks, Load *task_workload, const Id &nPEs, Load *PE_workload, const Id &nchunks) {
    auto chunk_sizes = compute_chunksizes(ntasks, task_workload, nchunks);
    auto chunk_loads = compute_chunkloads(task_workload, chunk_sizes, nchunks);
    auto chunk_offset = compute_cummulativesum<Id>(chunk_sizes, nchunks);
    
    Id *chunk_map = new Id[nchunks];
    for(Id i = 0; i < nchunks; ++i)
      chunk_map[i] = i;

    /* Organize the chunks in decreasing order */
    insertion_sort<Load, Id, true>(chunk_map, chunk_loads, nchunks);

    /* Iterate over the chunks, starting from the largest, and assign them to PEs */
    for(Id i = nchunks; i > 0; --i) {
      const Id idx = i-1;
      const Id cur_chunk_idx = chunk_map[idx];
      Id pe_id = 0;

      if(chunk_loads[idx] == 0)
        continue;

      /* Find the least overloaded PE */
      for(Id j = 1; j < nPEs; ++j)
        if(PE_workload[j] < PE_workload[pe_id])
          pe_id = j;

      /* Assign every task in the selected chunk to the same PE. */
      for(Id j = 0; j < chunk_sizes[cur_chunk_idx]; ++j)
        map[chunk_offset[cur_chunk_idx] + j] = pe_id;

      /* Update the load on the PE */
      PE_workload[pe_id] += chunk_loads[idx];
    }

    /* Clean memory */
    delete [] chunk_sizes;
    delete [] chunk_loads;
    delete [] chunk_offset;
    delete [] chunk_map;
  }
};

}}