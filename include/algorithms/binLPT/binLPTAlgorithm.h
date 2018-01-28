#pragma once

#include <structures/binLPT/chunkSorting.h>
#include <iostream>

namespace BinLPT {

/**
 * @brief The structure that encapsulate the algorithms used in the BinLPT strategy.
 * @type Load The type definition of the Load the BinLPT algorithm will use.
 * @type UInt the type definition of the Unsigned Integer the BinLPT algorithm will use.
 */
template<typename Load, typename UInt>
struct Algorithms {

  using Chunks = TaskChunks<Load, UInt>;
  using LoadInfo = LoadSetInfo<Load, UInt>;
  using ChunkSort = ChunkSorting<Load, UInt, std::is_integral<Load>::value>;

  /**
   * Create the chunk of tasks that will be assigned to the system's PUs.
   * @param load_info A structure that defines the characteristics of the tasks load.
   */
  inline static void partitionChunks(const LoadInfo &load_info) {
    UInt chunk_i = 0;
    auto chunks_ref = load_info.chunks;
    
    // For each load data, iterate.
    for(UInt i = 0; i < load_info.loads->size(); ++i) {
      // If the current chunk has already more load than the expected average...
      if(chunks_ref->load_sum[chunk_i] >= load_info.load_avg)
        // increment the chunk i to the next chunk available.
        chunk_i = (chunk_i+1)%chunks_ref->size;
      // Add the task to the chunk.
      chunks_ref->addTask(chunk_i, i, load_info.loads->at(i));
    }
  }

  /**
   * This method sort the chunks in descending order to be used in the chunk assigning phase.
   * @param load_info The load information that has been used in the partitioning phase.
   * @return A vector of indices to access the chunks in the TaskChunk structure.
   */
  static const std::vector<UInt> sortChunks(const LoadInfo &load_info) {
    const UInt &index_size = load_info.chunks->size;
    std::vector<UInt> ordered_indexes(index_size);
    
    for(UInt i = 0; i < index_size; ++i) {
      ordered_indexes[i] = i;
    }

    ChunkSort::function(load_info, ordered_indexes);

    return ordered_indexes;
  }

};

}