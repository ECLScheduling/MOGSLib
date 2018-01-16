#pragma once

#include <vector>

namespace BinLPT {

/**
 * @brief Structure that holds reference to an indice of grouped tasks.
 * @details This structure is used to group tasks (originally loop iterations) to be used within BinLPT algorithm.
 */
template<typename Load, typename UInt>
struct TaskChunk {
  
  /*
   * The indice of task ids grouped by this chunk.
   */
  std::vector<UInt> it_indice;

  /**
   * The sum of all iteration loads grouped by this Chunk.
   */
  Load load_sum = 0;

  /**
   * Add a task to the Chunk.
   * @param task_index The index of the added task.
   * @param load The load of the added task.
   */
  inline void addTask(const UInt &task_index, const Load load) {
    load_sum += load;
    it_indice.push_back(task_index);
  }

  /**
   * Compares this chunk's load sum to another chunk's.
   * @param other The other chunk to compare against.
   */
  inline const bool operator <(const TaskChunk &other) {
    return load_sum < other.load_sum;
  }

  /**
   * Compares this chunk's load sum to another chunk's.
   * @param other The other chunk to compare against.
   */
  inline const bool operator >(const TaskChunk &other) {
    return load_sum > other.load_sum;
  }

};

}