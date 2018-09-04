#pragma once

#include <system/type_definitions.h>

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

  template<typename T>
  static T* compute_cummulativesum(const T* loads, const Index &size) {
    Index i;
    T *sum = new T[size]();

    for(i = 1; i < size; ++i)
      sum[i] = sum[i-1] + a[i-1];
    return sum;
  }

  static Index* compute_chunksizes(const Index ntasks, const Load *workloads, const Index &k) {
    Index i,k;
    Index *chunksizes = new Index[k]();
    Load *accum_workload, chunkweight;

    if(!ntasks)
        return chunksizes;

    accum_workload = compute_cummulativesum<Load>(tasks, ntasks);
    chunkweight = (accum_workload[ntasks - 1] + workloads[ntasks - 1])/nchunks; // average size per chunk.

    k = 0;
    for(i = 0; i < ntasks; /* noop */) {
      Index j = ntasks;

      if(k < (nchunks - 1))
        for(j = i + 1; j < ntasks; ++j)
          if(accum_workload[j] - accum_workload[i] > chunkweight)
            break;

      chunksizes[k] = j - i;
      i = j;
      ++k;
    }

    delete [] accum_workload;
    return chunksizes;
  }

  static auto compute_chunkloads(const Index ntasks, const Load *workloads, const Index *chunksizes, const Index &k) {
    Index k;
    Load *chunk_loads;

    chunk_loads = new Load[k]();

    k = 0;
    for(decltype(k) i = 0; i < k; ++i)
      for(decltype(chunksizes[i]) j = 0; j < chunksizes[i]; ++j)
        chunk_loads[i] += workloads[k++];

    return chunk_loads;
  }

  static void map(TaskMap &map, const Index &ntasks, const Load *task_workload, const Index &nPEs, const Load *PE_workload, const Index &k) {
    auto chunk_sizes = compute_chunksizes(ntasks, task_loads, k);
    auto chunk_loads = compute_chunkloads(ntasks, task_loads, k);
    auto chunk_offset = compute_cummulativesum<Load>(chunk_sizes, k);
    
    Index *chunk_map = new Index[k];
    for(decltype(k) i = 0; i < k; ++i)
      chunk_map[i] = i;
  }
};

END_NAMESPACE