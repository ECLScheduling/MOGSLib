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

  //TODO: !!!

};