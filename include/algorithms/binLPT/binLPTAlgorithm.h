#pragma once

#include <algorithms/utility.h>
#include <cassert>
#include <cstring>

namespace BinLPT {

/**
 * @brief The structure that encapsulate the algorithms used in the BinLPT strategy.
 *
 * @type Load The type definition of the Load the BinLPT algorithm will use.
 * @type UInt the type definition of the Unsigned Integer the BinLPT algorithm will use.
 */
template<typename Load, typename UInt>
struct Algorithms {

  /**
   * @brief Computes chunk sizes.
   *
   * @param tasks   Target tasks.
   * @param ntasks  Number of tasks.
   * @param nchunks Number of chunks.
   *
   * @returns Chunk sizes.
   */
  inline static UInt *compute_chunksizes(const Load* tasks, const UInt ntasks, const UInt nchunks) {
    UInt i, k;
    UInt *chunksizes = new UInt[nchunks]();
    Load *workload, chunkweight;

    assert(chunksizes != nullptr);
    assert(nchunks > 0);

    if(!ntasks)
      return chunksizes;

    workload = UtilityAlgorithms::compute_cummulativesum<Load>(tasks, ntasks);
    chunkweight = (workload[ntasks - 1] + tasks[ntasks - 1])/nchunks;

    /* Compute chunksizes. */
    k = 0;
    for (i = 0; i < ntasks; /* noop */)
    {
      UInt j = ntasks;

      if (k < (nchunks - 1))
      {
        for (j = i + 1; j < ntasks; j++)
        {
          if (workload[j] - workload[i] > chunkweight)
          break;
        }
      }

      chunksizes[k] = j - i;
      i = j;
      k++;
    }

    delete workload;
    return (chunksizes);
  }

  /**
   * @brief Computes chunks loads.
   *
   * @param tasks The task loads.
   * @param ntasks The size of tasks.
   * @param chunksizes The size of the chunks.
   * @param nchunks The size of the chunksizes array.
   */
  inline static Load *compute_chunkloads(const Load *tasks, UInt ntasks, const UInt *chunksizes, const UInt nchunks) {
    UInt i, k;    /* Loop indexes. */
    Load *chunk_loads; /* Chunks.       */

    chunk_loads = new Load[nchunks]();
    assert(chunk_loads != nullptr);

    /* Compute chunks. */
    k = 0;
    for (i = 0; i < nchunks; ++i)
    {
      UInt j;

      assert(k <= ntasks);

      for (j = 0; j < chunksizes[i]; ++j)
        chunk_loads[i] += tasks[k++];
    }

    return (chunk_loads);
  }
};

}