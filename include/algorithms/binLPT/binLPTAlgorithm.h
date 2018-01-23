#pragma once

#include <structures/binLPT/chunkSorting.h>
#include <iostream>

namespace BinLPT {

/**
 * The default definition of the BinLPT callback class.
 * @details A class that formulates a strategy output must implement the methods of this virtual class in order to be able to use the BinLPT Algorithm.
 * @type Load The type definition of the Load the BinLPT algorithm will use.
 * @type UInt the type definition of the Unsigned Integer the BinLPT algorithm will use.
 */
template<typename Load, typename UInt>
class AlgorithmCallback {
public:
  
  /**
   * This method is called everytime the binLPT algorithm maps a chunk of tasks to a PE.
   * @details Inside this method the load of the PE must be adjusted to match it's received tasks. In addition, this callback must register the addition to formulate the strategy output.
   * @param task_count The amount of tasks that are being added to the PE.
   * @param to_PE The PE that has received the task.
   */
  virtual void algorithmMapped(const std::vector<UInt> *task_indexes, const UInt &to_PE, const Load &total_load) = 0;
};

/**
 * The structure that encapsulate the algorithms used in the BinLPT strategy.
 * @type Load The type definition of the Load the BinLPT algorithm will use.
 * @type UInt the type definition of the Unsigned Integer the BinLPT algorithm will use.
 * @type CallbackType A type that has the method algorithmMapped, that will be called everytime a task is mapped to a PE in the algorithm.
 */
template<typename Load, typename UInt, typename CallbackType>
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

  /**
   * This method decides the assignment of the chunks to the PEs in the input.
   * @details The actual assignment is made through the class that implementes the callback signature.
   * @param load_info The information about the load and chunks.
   * @param chunk_ordered_indexes The sequence of indexes to be accessed to find the chunks in a decrescent order.
   * @param callback A reference to the object that implements the callback method and will be responsible to formulate the output.
   */
   static void assignChunks(const LoadInfo &load_info, const std::vector<UInt> &chunk_ordered_indexes, CallbackType *callback){
     for(auto i : chunk_ordered_indexes) {
       auto task_vector = &(load_info.chunks->tasks[i]);
       UInt to_PE = 0; //TODO: Escolha do PE.

       callback->algorithmMapped(task_vector, to_PE, load_info.chunks->load_sum[i]);
     }
   }

};

}