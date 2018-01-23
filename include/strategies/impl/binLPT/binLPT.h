#pragma once

#include "binLPTAdaptorRequirements.h"

#include <strategies/strategyInterface.h>
#include <algorithms/binLPT/binLPTAlgorithm.h>
#include <iostream>

namespace BinLPT {

/**
 * @brief This class encapsulates the implementation of the BinLPT strategy.
 * @details The BinLPT strategy was originally implemented for OpenMP to act as a loop scheduler.
 */
template <typename InputAdaptor>
class Strategy : public StrategyInterface<InputAdaptor>, public AlgorithmCallback<typename InputAdaptor::Load, typename InputAdaptor::UInt> {
  static_assert(BinLPTAdaptorRequirements<InputAdaptor>::value, "Input Adaptor must implement the WithGenericStructure<UInt> adaptor extension.");

public: 

  using Load = typename InputAdaptor::Load;
  using Id = typename InputAdaptor::Id;
  using UInt = typename InputAdaptor::UInt;

  using AlgorithmSet = Algorithms<Load, UInt, Strategy>;
  using LoadInfo = typename AlgorithmSet::LoadInfo;

protected:

  /**
   * @variable A variable that saves the state between the different BinLPT algorithm stages.
   */
  LoadInfo *load_info;

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
   * Executes the assign phase of the BinLPT algorithm.
   * @details This phase is where the chunks are assigned to the system's PE in a greedy fashion.
   * @param chunk_ordering The indexes list that the chunks must be accessed to assert a decreasing order.
   */
  void assignPhase(const std::vector<UInt> chunk_ordering);

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

  /**
   * This method is called everytime the BinLPT algorithm maps a task chunk to a PE.
   * @details Inside this method the load of the task must be adjusted to match it's addition to the PE's mapped tasks.
   * @param task_indexes The tasks indexes that have been mapped.
   * @param to_PE The PE that has received the task chunk.
   * @param total_load The load sum of the tasks that are being mapped.
   */
  inline void algorithmMapped(const std::vector<UInt> *task_indexes, const UInt &to_PE, const Load &total_load) {
    auto &output = StrategyInterface<InputAdaptor>::strategyOutput;
    auto &input = StrategyInterface<InputAdaptor>::currentInput;

    // Set the mapping as part of the output.
    for(auto task : *task_indexes)
      output.set(input->PEIds()[to_PE], input->taskIds()[task]);
    
    // Adjust the PE load.
    input->PELoads()[to_PE] += total_load;
  }

  ~Strategy() {
    clearLoadInfo(); 
  }

};

#include "binLPT.ipp"

}