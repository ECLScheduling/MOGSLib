#pragma once

#include <type_traits>
#include <cstdlib>

#include <structures/binLPT/taskChunk.h>
#include <structures/binLPT/loadsetInfo.h>

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
  inline static void function(const LoadInfo &load_info, Chunk * const chunks_ref) {
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

  void countSort(Chunk * const chunks_ref, const UInt &size, const Load &min, const Load &max) {
    const UInt bucket_size = max - min;

    std::vector<Chunk* const> *bucket = new std::vector<Chunk* const>[bucket_size];

    for(UInt i = 0; i < size; ++i)
      bucket[chunks_ref[i].load_sum].push_back(chunks_ref+i);

    for(UInt i = 0; i < bucket_size; ++i) {
      //TODO: parei aqui!!
    }
  }

  /**
   * The counting-sort function implementation.
   */
  inline static void function(const LoadInfo &load_info, Chunk * const chunks_ref) {
    // implement Counting-Sort.
  }
};

}