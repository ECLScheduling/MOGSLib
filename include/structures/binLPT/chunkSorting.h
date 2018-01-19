#pragma once

#include <type_traits>
#include <map>
#include <cstdlib>

#include <structures/binLPT/taskChunk.h>
#include <structures/binLPT/loadsetInfo.h>
#include <iostream>

namespace BinLPT {

/**
 * @brief A meta-programed structure to hold the sorting method used in the binLPT algorithm.
 * @details If counting sort is possible (when Load is of type unsigned int) it will be compiled and used, otherwise quick-sort will be used instead.
 * @note This method will sort in a descending order.
 */
template<typename Load, typename UInt, bool counting_sort_possible>
struct ChunkSorting {
  
  using LoadInfo = LoadSetInfo<Load, UInt>;
  using Chunk = TaskChunk<Load, UInt>;

  /**
   * The sorting function implementation when counting-sort is not possible due to the Load typename.
   */
  inline static void function(const LoadInfo &load_info, Chunk *chunks_ref) {
    std::qsort(chunks_ref, load_info.chunks_size, sizeof *chunks_ref, [](const void *a, const void *b) {
      Chunk arg1 = *static_cast<const Chunk *>(a);
      Chunk arg2 = *static_cast<const Chunk *>(b);

      if(arg1 < arg2) return 1; // This is the inverse of a normal quick-sort due to the need to sort in decrescent order.
      if(arg1 > arg2) return -1; // This is the inverse of a normal quick-sort due to the need to sort in decrescent order.
      return 0;
    });
  }

};

/**
 * The specialization of ChunkSorting for when using Load type as a form of unsigned integer.
 * @note This method will sort in a descending order.
 */
template<typename Load, typename UInt>
struct ChunkSorting<Load, UInt, true> {
  
  using LoadInfo = LoadSetInfo<Load, UInt>;
  using Chunk = TaskChunk<Load, UInt>;

  static void countSort(Chunk *chunks_ref, const UInt &size, const Load &max_val) {
    std::map<Load, std::vector<Chunk*>* > chunk_bucket;

    for(UInt i = 0; i < size; ++i){
      auto key = chunks_ref[i].load_sum;
      
      std::cout << "Inserting into position " << key << std::endl;
      if(chunk_bucket.find(key) == chunk_bucket.end()){
        chunk_bucket[key] = new std::vector<Chunk*>(size);
        std::cout << "First time for this position " << key << std::endl;
      }
      chunk_bucket[key]->push_back(&chunks_ref[i]);
    }

    for (auto it = chunk_bucket.rbegin(); it != chunk_bucket.rend(); ++it) {
      std::cout << "Key: " << it->first << std::endl;
      //TODO: Put them back in the index as output.
    }

    // while(output_i < size) {
    //   while(bucket[chunk_i].size() == 0) {
    //     ++chunk_i;
    //   }
    //   std::cout << "Position " << chunk_i << " had elements" << std::endl;
    //   auto cur_bucket = bucket[chunk_i];
    //   for(UInt j = 0; j < cur_bucket.size(); ++j) {
    //     chunks_ref[output_i] = *cur_bucket[j];
    //     ++output_i;
    //   }
    //   ++chunk_i;
    // }
  }

  /**
   * The counting-sort function implementation.
   */
  inline static void function(const LoadInfo &load_info, Chunk *chunks_ref) {
    countSort(chunks_ref, load_info.chunks_size, load_info.load_sum);
  }
};

}