#pragma once

#include "binLPTAdaptorRequirements.h"

#include <strategies/strategyInterface.h>
#include <algorithms/binLPT/binLPTAlgorithm.h>
#include <iostream>

namespace BinLPT {

/**
 * A comparator structure used to order the PE indexes by their load in a crescent ordering.
 * @type Load The load type that will be indirectly compared by the comparator.
 * @type UInt The type used as unsigned integer (index) in this comparator.
 */
template<typename Load, typename UInt>
struct LoadReverseComparator {
  std::vector<Load> *loads;
  
  /**
   * @details This behaviour is the oposite behaviour of a classic comparator object.
   * @param a The first index.
   * @param b The second index.
   * @return true if the load, stored in the loads pointer, in the index a is GREATER than the load in the index b.
   */
  bool operator ()(const UInt &a, const UInt &b) {
    return loads->at(a) > loads->at(b);
  }

};

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

  using LoadComp = LoadReverseComparator<Load, UInt>;

protected:

  /**
   * @variable A variable that saves the state between the different BinLPT algorithm stages.
   */
  LoadInfo *load_info = nullptr;

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
   * @param PE_index The index of the PE in the input that has received the task chunk.
   * @param total_load The load sum of the tasks that are being mapped.
   */
  inline void algorithmMapped(const std::vector<UInt> *task_indexes, const UInt &PE_index, const Load &total_load) {
    auto &output = StrategyInterface<InputAdaptor>::strategyOutput;
    auto &input = StrategyInterface<InputAdaptor>::currentInput;

    // Set the mapping as part of the output.
    for(auto task : *task_indexes){
      output.set(input->PEIds()[PE_index], input->taskIds()[task]);
    }
    
    // Adjust the PE load.
    input->PELoads()[PE_index] += total_load;
  }

  ~Strategy() {
    clearLoadInfo(); 
  }

};

#include "binLPT.ipp"

}