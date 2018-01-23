#pragma once

#include <structures/binLPT/taskChunks.h>
#include <vector>

namespace BinLPT {

/**
 * @brief Structure that holds information about the predicted load used in the BinLPT algorithm.
 */
template<typename Load, typename UInt>
struct LoadSetInfo {

  using Chunks = TaskChunks<Load, UInt>;

  /**
   * The sum of all task loads.
   */
  Load load_sum;

  /**
   * The average load based on the desired amount of chunks.
   */
  Load load_avg;

  /**
   * The maximum load value of all tasks, used for counting sort.
   */
  Load load_max;

  /**
   * The minimum load value of all tasks, used for optimizing counting sort.
   */
  Load load_min;

  /**
   * A reference pointer to all the load values of the tasks.
   */
  std::vector<Load> *loads;

  /**
   * A reference to the task chunks.
   */
  Chunks *chunks;

  /**
   * Creates a LoadSetInfo structure initialized through the analyzis of an array of load values.
   * @param loads The array of load values corresponding to a set of tasks.
   * @param max_chunks The maximum desired amount of chunks to be created by BinLPT for this dataset.
   * @return A LoadSetInfo structure initialized to be used in the BinLPT partitioning phase.
   */
  static LoadSetInfo *analyzeLoadArray(std::vector<Load> &load_vector, const UInt &max_chunks) {
    LoadSetInfo *load_info = new LoadSetInfo();
    auto size = load_vector.size();

    load_info->loads = &load_vector;
    load_info->chunks = new Chunks(max_chunks);

    for(UInt i = 0; i < size; ++i) {
      // Calculate the load sum.
      load_info->load_sum += load_vector[i];
      
      // Find the maximum load.
      if(load_info->load_max < load_vector[i])
        load_info->load_max = load_vector[i];
      // Find the minimum load.
      if(load_info->load_min > load_vector[i])
        load_info->load_min = load_vector[i];
    }    

    // Calculate the load average.
    load_info->load_avg = load_info->load_sum / load_info->chunks->size;
    if(load_info->load_avg == 0)
      load_info->load_avg = 1;
    return load_info;
  }

  /**
   * LoadInfo default constructor to initialize every atribute to 0.
   */
  LoadSetInfo() {
    load_sum = 0;
    load_avg = 0;
    load_min = 0;
    load_max = 0;
    chunks = nullptr;
    loads = nullptr;  
  }

  ~LoadSetInfo() {
    if(chunks) {
      delete chunks;
      chunks = nullptr;
    }
  }

};

}