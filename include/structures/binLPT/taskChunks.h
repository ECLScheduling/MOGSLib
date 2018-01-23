#pragma once

#include <vector>
#include <cassert>
#include <cstring>

namespace BinLPT {

/**
 * @brief Structure that holds the chunks information in a data-oriented fashion.
 * @details A TaskChunk is a structure used to group tasks (originally loop iterations) to be used within BinLPT algorithm.
 */
template<typename Load, typename UInt>
struct TaskChunks {

  /**
   * The amount of chunks this structure represents.
   */
  UInt size;

  /*
   * The indice of task ids grouped by this chunk.
   */
  std::vector<UInt> *tasks;

  /**
   * The sum of all iteration loads grouped by this Chunk.
   */
  Load *load_sum;

  /**
   * Add a task index to a indexed chunk.
   * @param chunk_index The index of the chunk in this structure.
   * @param task_index The index of the added task.
   * @param load the load of the added task.
   */
  void addTask(const UInt &chunk_index, const UInt &task_index, const Load &load) {
    tasks[chunk_index].push_back(task_index);
    load_sum[chunk_index] += load;
  }

  TaskChunks() {
    load_sum = nullptr;
    tasks = nullptr;
  }

  /**
   * A constructor to be used when the amount of taskchunks is known beforehand.
   */
  TaskChunks(const UInt &chunk_count) {
    assert(chunk_count > 0); // The number of task chunks must be at least 1.

    size = chunk_count;
    load_sum = new Load[size];
    memset(load_sum, 0, size * sizeof(load_sum[0]));
    tasks = new std::vector<UInt>[size];
  }

  ~TaskChunks() {
    if(load_sum) {
      delete [] load_sum;
      load_sum = nullptr;
    }
    if(tasks) {
      delete [] tasks;
      tasks = nullptr;
    }
  }

};

}