#pragma once

#include "greedyPGStrategy.h"

#include <omp.h>

/**
 * This stategy employs the Greedy and Penalized Graph strategy in a parallel fashion.
 */
class GreedyParallelPGStrategy : public GreedyPenalizedGraphStrategy {

public:

  /**
   * Method to create this strategy with a said penality function
   */
  GreedyParallelPGStrategy(const PGAlgorithm::PenalityFunction &penalityFunction) : GreedyPenalizedGraphStrategy(penalityFunction) {}

  virtual ~GreedyParallelPGStrategy() {}

protected:

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The Load Balancer's input
   */
  virtual void doTaskMapping(const NaiveBasicInput &input) {
    #pragma omp parallel
    {
      MaxHeap tasks;
      MinHeap PEs;

      populatePEHeap(input, &PEs);
      populateTaskHeap(input, &tasks);

      executeGreedyStrategy(&tasks, &PEs);
      populateOutput(PEs);
    }
  }

};