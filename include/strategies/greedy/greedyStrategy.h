#pragma once

#include <interfaces/strategy/strategyInterface.h>
#include <algorithms/greedy/greedyAlgorithm.h>

#include <vector>
#include <algorithm>

/**
 * @brief This class encapsulates the implementation of a Greedy load balancer strategy.
 */
template <typename InputAdaptor>
class GreedyStrategy : public StrategyInterface<InputAdaptor>, public GreedyAlgorithmCallback<typename InputAdaptor::Id, typename InputAdaptor::Id> {
public: 
  
  using Load = typename InputAdaptor::Load;
  using Id = typename InputAdaptor::Id;
  using UInt = typename InputAdaptor::UInt;

private:

  /**
   * A sctructure to compare Tasks in conformity to their load.
   */
  struct MaxHeapComparator {
    InputAdaptor * const strategyInput;

    MaxHeapComparator(InputAdaptor *inputAdaptor) : strategyInput(inputAdaptor) {}

    inline bool operator ()(const Id &a, const Id &b) const {
      return strategyInput->taskLoad(a) < strategyInput->taskLoad(b);
    }
  };

  /**
   * A sctructure to compare PEs in conformity to their load.
   */
  struct MinHeapComparator {
    InputAdaptor * const strategyInput;

    MinHeapComparator(InputAdaptor *inputAdaptor) : strategyInput(inputAdaptor) {}

    inline bool operator ()(const Id &a, const Id &b) const {
      return strategyInput->PELoad(a) > strategyInput->PELoad(b);
    }
  };

public:

  using GreedyAlgorithm = GreedyStrategyAlgorithm<Id, Id, GreedyStrategy>;
  using MaxHeap = typename GreedyAlgorithm::MaxHeap;
  using MinHeap = typename GreedyAlgorithm::MinHeap;

  /**
   * This method is called everytime the greedy algorithm maps a task to a PE.
   * @details Inside this method the load of the task must be adjusted to match it's addition to the PE's mapped tasks.
   * @param task The task that has been mapped.
   * @param toPE The PE that has received the task.
   */
  inline void algorithmMapped(const Id &task, const Id &toPE) {

    // Set the mapping as part of the output.
    StrategyInterface<InputAdaptor>::strategyOutput.set(toPE, task);

    // Adjust the load of the PE as the current PE's load plus the task's load.
    auto inputAdaptorPtr = StrategyInterface<InputAdaptor>::currentInput;
    auto newLoad = inputAdaptorPtr->PELoad(toPE) + inputAdaptorPtr->taskLoad(task);
    
    inputAdaptorPtr->setPELoad(toPE, newLoad);
  }

protected:

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The strategy's input
   */
  void doTaskMapping(InputAdaptor &input);

};

#include "greedyStrategy.ipp"