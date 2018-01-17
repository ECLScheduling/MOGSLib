#pragma once

#include <structures/binLPT/chunkSorting.h>

namespace BinLPT {

/**
 * The structure that encapsulate the algorithms used in the BinLPT strategy.
 */
template<typename Load, typename UInt>
struct Algorithms {

  using Chunk = TaskChunk<Load, UInt>;
  using LoadInfo = LoadSetInfo<Load, UInt>;
  using ChunkSort = ChunkSorting<Load, UInt, std::is_unsigned<Load>::value && std::is_integral<Load>::value>;

  /**
   * Create the chunk of tasks that will be assigned to the system's PUs.
   * @param load_info A structure that defines the characteristics of the tasks load.
   * @param chunks_ref A pointer to an array of pre-allocated chunks containing at least the maximum desired amount of chunks allocated.
   */
  inline static void partitionChunks(const LoadInfo &load_info, Chunk * const chunks_ref) {
    UInt chunk_i = 0;
    
    // For each load data, iterate.
    for(UInt i = 0; i < load_info.load_size; ++i) {
      // If the current chunk has already more load than the expected average...
      if(chunks_ref[chunk_i].load_sum >= load_info.load_avg)
        // increment the chunk i to the next chunk available.
        chunk_i = (chunk_i+1)%load_info.chunks_size;
      // Add the task to the chunk.
      chunks_ref[chunk_i].addTask(i, load_info.loads[i]);
    }
  }

  /**
   * This method sort the chunks in descending order to be used in the chunk assigning phase.
   * @param load_info The load information that has been used in the partitioning phase.
   * @param chunks_ref A reference to the memory location where the chunks are allocated.
   * @return This method rearrange the chunks in the chunks_ref pointer.
   */
  inline static void sortChunks(const LoadInfo &load_info, Chunk * const chunks_ref) {
    ChunkSort::function(load_info, chunks_ref);    
  }

  inline static void assignChunk(){}
};

}