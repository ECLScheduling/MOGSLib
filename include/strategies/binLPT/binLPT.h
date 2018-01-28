#pragma once

#include "binLPTAdaptorRequirements.h"

#include <interfaces/strategy/strategyInterface.h>
#include <algorithms/binLPT/binLPTAlgorithm.h>

namespace BinLPT {

/**
 * @brief This class encapsulates the implementation of the BinLPT strategy.
 * @details The BinLPT strategy was originally designed for OpenMP to act as a loop scheduler.
 */
template <typename InputAdaptor>
class Strategy : public StrategyInterface<InputAdaptor> {
  static_assert(BinLPTAdaptorRequirements<InputAdaptor, typename InputAdaptor::UInt>::value, "Input Adaptor must implement the WithGenericStructure<UInt> adaptor extension using the same UInt as the remainder of the system. The default UInt is defined in Traits<void>.");

public: 

  using Load = typename InputAdaptor::Load;
  using UInt = typename InputAdaptor::UInt;

  using AlgorithmSet = Algorithms<Load, UInt>;
  using LoadInfo = typename AlgorithmSet::LoadInfo;

  using LoadComp = LoadReverseComparator<Load, UInt>;

protected:

  /**
   * @variable A variable that saves the state between the different BinLPT algorithm stages.
   */
  LoadInfo *load_info = nullptr;

  /**
   * @variable PE_ids A vector of indices to access the PE's input data.
   * @details This variable is used to represent an order of access to the PE data since the data needs to be sorted in this strategy.
   */
  std::vector<UInt> PE_ids;

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   */
  void doTaskMapping();

  /**
   * Executes the partitioning phase of the BinLPT algorithm.
   * @details This phase encapsulates the partitioning and sorting of the tasks into a set of ordered task chunks.
   * @return Outputs the ordering to access the task chunks within the load_info chunk information.
   */
  std::vector<UInt> partitioningPhase();

  /**
   * This method decides the assignment of the chunks to the PEs in the input.
   * @details This method uses a binary heap to order the PEs in increasing ordering, thus applying the LPT rule to the assigning phase.
   * @param chunk_ordered_indexes The sequence of indexes to be accessed to find the chunks in a decrescent order.
   */
  void assignPhase(const std::vector<UInt> chunk_ordered_indexes);

  /**
   * This method is called everytime the BinLPT algorithm maps a task chunk to a PE.
   * @details Inside this method the load of the task must be adjusted to match it's addition to the PE's mapped tasks.
   * @param task_indexes The tasks indexes that have been mapped.
   * @param PE_index The index of the PE in the input that has received the task chunk.
   * @param total_load The load sum of the tasks that are being mapped.
   */
  void assignChunk(const std::vector<UInt> *task_indexes, const UInt &PE_index, const Load &total_load);

  /**
   * Clear any memory that may still be pointed by load_info.
   */
  inline void clearLoadInfo() {
    if(load_info) {
      delete load_info;
      load_info = nullptr;
    }
  }

public:

  ~Strategy() {
    clearLoadInfo(); 
  }

};

#include "binLPT.ipp"

}