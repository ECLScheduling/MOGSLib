#pragma once

#include <type_traits>
#include <algorithm>
#include <vector>
#include <map>

#include <structures/binLPT/taskChunks.h>
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
  using Chunks = TaskChunks<Load, UInt>;

  /**
   * The sorting function implementation when counting-sort is not possible due to the Load typename.
   */
  inline static void function(const LoadInfo &load_info, std::vector<UInt> &chunk_indexes) {
    auto chunks = load_info.chunks;

    std::sort(chunk_indexes.begin() , chunk_indexes.end(), [&chunks](UInt a, UInt b) {
      return chunks->load_sum[a] > chunks->load_sum[b];
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
  using Chunks = TaskChunks<Load, UInt>;

  /**
   * A counting sort implementation that looks the chunk load sum to order a set of indice to TaskChunk representations.
   * @details This function modifies the chunk_indexes reference input.
   * @param chunks_ref A reference to the Chunks data-oriented structure.
   * @param chunk_indexes A initial reference list of valid indice to the task chunk representations in chunks_ref.
   */
  static void countSort(Chunks *chunks_ref, std::vector<UInt> &chunk_indexes) {
    std::map<Load, std::vector<UInt> > chunk_indice_bucket;

    for(UInt i = 0; i < chunks_ref->size; ++i){
      auto key = chunks_ref->load_sum[i];
      
      if(chunk_indice_bucket.find(key) == chunk_indice_bucket.end()){
        chunk_indice_bucket[key] = std::vector<UInt>();
      }
      chunk_indice_bucket.at(key).push_back(i);
    }

    UInt i = 0;
    for (auto it = chunk_indice_bucket.rbegin(); it != chunk_indice_bucket.rend(); ++it) {
      std::vector<UInt> &indice_vector = it->second;
      for(auto chunk_index : indice_vector) {
        chunk_indexes[i] = chunk_index;
        ++i;
      }
    }
  }

  /**
   * The counting-sort function implementation.
   * @param load_info The reference to the load_info structure.
   */
  inline static void function(const LoadInfo &load_info, std::vector<UInt> &chunk_indexes) {
    countSort(load_info.chunks, chunk_indexes);
  }
};

}