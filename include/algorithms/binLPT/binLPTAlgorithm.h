#pragma once

#include <structures/binLPT/taskChunk.h>
#include <structures/binLPT/loadsetInfo.h>

namespace BinLPT {

/**
 * The structure that encapsulate the algorithms used in the BinLPT strategy.
 */
template<typename Load, typename UInt>
struct Algorithms {

  using Chunk = TaskChunk<Load, UInt>;
  using LoadInfo = LoadSetInfo<Load, UInt>;

  /**
   * Create the chunk of tasks that will be assigned to the system's PUs.
   * @param load_info A structure that defines the characteristics of the tasks load.
   * @param chunks_ref A pointer to an array of pre-allocated chunks containing at least the maximum desired amount of chunks allocated.
   * @return The amount of actual used chunks in the partitioning phase
   */
  static const UInt& partitionChunks(const LoadInfo &load_info, Chunk const *chunks_ref) {
    UInt chunk_i = 0;
    
    // For each load data, iterate.
    for(UInt i = 0; i < load_info.load_size; ++i) {
      // If the current chunk has already more load than the expected average...
      if(chunks_ref[chunk_i].load_sum > load_info.load_avg)
        // increment the chunk i to the next chunk available.
        chunk_i = (chunk_i+1)%load_info.chunks_size;
      // Add the task to the chunk.
      chunks_ref[chunk_i].addTask(i, load_info.loads[i]);
    }
    // Return the amount of chunks used within the loop (because of module, this number will never be greater than the maximum expected amount of chunks)
    return chunk_i+1;
  }

  void sortChunks(Load *loads, const UInt &loadSize){}
  void assignChunk(){}
};

}