#pragma once

#include <cassert>

namespace BinLPT {

/**
 * @brief Structure that holds information about the predicted load used in the BinLPT algorithm.
 */
template<typename Load, typename UInt>
struct LoadSetInfo {

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
   * A reference pointer to all the load values of the tasks.
   */
  Load *loads;

  /**
   * The amount of load values that the loads pointer points to.
   */
  UInt load_size;

  /**
   * The desired amount of chunks that will be created in the BinLPT partitioning phase.
   */
  UInt chunks_size;

  /**
   * Creates a LoadSetInfo structure initialized through the analyzis of an array of load values.
   * @param loads The array of load values corresponding to a set of tasks.
   * @param load_size The size of the loads array.
   * @param max_chunks The maximum desired amount of chunks to be created by BinLPT for this dataset.
   * @return A LoadSetInfo structure initialized to be used in the BinLPT partitioning phase.
   */
  static const LoadSetInfo analyzeLoadArray(Load * const &loads, const UInt &load_size, const UInt &max_chunks) {
    assert(max_chunks > 0); // The maximum number of chunks must be at least 1.

    LoadSetInfo load_info;

    load_info.loads = loads;
    load_info.chunks_size = max_chunks;
    load_info.load_size = load_size;

    for(UInt i = 0; i < load_size; ++i) {
      load_info.load_sum += loads[i];
      
      if(load_info.load_max < loads[i])
        load_info.load_max = loads[i];
    }    

    load_info.load_avg = load_info.load_sum / load_info.chunks_size;
    return load_info;
  }

  /**
   * LoadInfo default constructor to initialize every atribute to 0.
   */
  LoadSetInfo() {
    load_sum = 0;
    load_avg = 0;
    load_max = 0;
    load_size = 0;
    chunks_size = 0;
    loads = NULL;  
  }

};

}