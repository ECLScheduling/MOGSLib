#pragma once

BEGIN_NAMESPACE(Policy)

/**
 * @brief A workload-aware policy that packs adjacent tasks together and distribute them in a greedy fashion.
 */
template<typename _Load = MOGSLib::Load>
class BinLPT {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;
  using Load = _Load;

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
   * @type UInt The unsigned integer type to be used as the array index.
   * @type decreasing_order A boolean to choose whether the algorithm should organize in ascending order or not. This value defaults to increasing order.
   *
   * @param map The original indices of the elements in a.
   * @param a The array of elements to be sorted.
   * @param n the size of the array a.
   **/
  template <typename T, typename UInt, bool decreasing_order = true>
  static void insertion_sort(UInt *map, T *a, const UInt n) {
    UInt i, j; /* Loop indexes.    */
    
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
  static T* compute_cummulativesum(const T* arr, const Index &size) {
    Index i;
    T *sum = new T[size]();

    for(i = 1; i < size; ++i)
      sum[i] = sum[i-1] + arr[i-1];
    return sum;
  }

  static Index* compute_chunksizes(const Index ntasks, const Load *workloads, const Index &nchunks) {
    Index i, cur_chunk;
    Index *chunksizes = new Index[nchunks]();
    Load *accum_workload, chunkweight;

    if(!ntasks)
      return chunksizes;

    accum_workload = compute_cummulativesum<Load>(workloads, ntasks);
    chunkweight = (accum_workload[ntasks - 1] + workloads[ntasks - 1])/nchunks; // average size per chunk.

    cur_chunk = 0;
    for(i = 0; i < ntasks; ++cur_chunk) {
      Index j = ntasks;

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

  static auto compute_chunkloads(const Load *workloads, const Index *chunksizes, const Index &k) {
    Index cur_chunk;
    Load *chunk_loads;

    chunk_loads = new Load[k]();

    cur_chunk = 0;
    for(Index i = 0; i < k; ++i)
      for(Index j = 0; j < chunksizes[i]; ++j)
        chunk_loads[i] += workloads[cur_chunk++];

    return chunk_loads;
  }

  static void map(TaskMap &map, const Index &ntasks, Load *task_workload, const Index &nPEs, Load *PE_workload, const Index &nchunks) {
    auto chunk_sizes = compute_chunksizes(ntasks, task_workload, nchunks);
    auto chunk_loads = compute_chunkloads(task_workload, chunk_sizes, nchunks);
    auto chunk_offset = compute_cummulativesum<Index>(chunk_sizes, nchunks);
    
    Index *chunk_map = new Index[nchunks];
    for(Index i = 0; i < nchunks; ++i)
      chunk_map[i] = i;

    /* Organize the chunks in decreasing order */
    insertion_sort<Load, Index, true>(chunk_map, chunk_loads, nchunks);

    /* Iterate over the chunks, starting from the largest, and assign them to PEs */
    for(Index i = nchunks; i > 0; --i) {
      const Index idx = i-1;
      const Index cur_chunk_idx = chunk_map[idx];
      Index pe_id = 0;

      if(chunk_loads[idx] == 0)
        continue;

      //std::cout << "\tWorkload in PE " << pe_id << " is " << PE_workload[pe_id] << std::endl;
      //std::cout << "\tWorkload in PE " << 1 << " is " << PE_workload[1] << std::endl;
      /* Find the least overloaded PE */
      for(Index j = 1; j < nPEs; ++j)
        if(PE_workload[j] < PE_workload[pe_id])
          pe_id = j;

      //std::cout << "Chunk " << cur_chunk_idx << " mapped to PE " << pe_id << std::endl;
      /* Assign every task in the selected chunk to the same PE. */
      for(Index j = 0; j < chunk_sizes[cur_chunk_idx]; ++j)
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

END_NAMESPACE