#pragma once

#include <strategies/abstractStrategy.h>
#include <algorithms/greedy/greedyAlgorithm.h>

#include <structures/simpleTask.h>
#include <structures/simplePE.h>

/**
 * This class encapsulates the implementation of a Greedy load balancer strategy.
 */
template <typename InputAdaptor>
class GreedyStrategy : public AbstractStrategy<InputAdaptor>{
public:

  using Load = typename InputAdaptor::Load;
  using Id = typename InputAdaptor::Id;
  using UInt = typename InputAdaptor::UInt;

  using Task = SimpleTask<Id, Load>;
  using PE = SimplePE<Task>;

private:

  /**
   * A sctructure to compare Tasks between itselves in conformity to their load.
   */
  struct MaxHeapComparator {
    inline bool operator ()(const Task *a, const Task *b) const {
      return *a < *b;
    }
  };

  /**
   * A sctructure to compare PEs between itselves in conformity to their load.
   */
  struct MinHeapComparator {
    inline bool operator ()(const PE *a, const PE *b) const {
      return *a > *b;
    }
  };

public:

  using GreedyAlgorithm = GreedyStrategyAlgorithm<Task, PE, MaxHeapComparator, MinHeapComparator>;
  using MaxHeap = typename GreedyAlgorithm::MaxHeap;
  using MinHeap = typename GreedyAlgorithm::MinHeap;

protected:

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The strategy's input
   */
  void doTaskMapping(InputAdaptor &input);

  /**
   * Construct the task heap to be used in the task mapping.
   */
  void constructTaskHeap(MaxHeap &maxHeap, Task * const tasks, const UInt &nTasks, InputAdaptor &input);

  /**
   * Construct the PE heap to be used in the task mapping.
   */
  void constructPEHeap(MinHeap &minHeap, PE * const PEs, const UInt &nPEs, InputAdaptor &input);

};

#include "greedyStrategy.ipp"