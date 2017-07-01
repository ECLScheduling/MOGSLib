#pragma once

#include <strategies/impl/penalizedGraph/greedyParallelPGStrategy.h>
#include <strategies/input/minimalParallelInput.h>

/**
 * The struct to be used by the StrategyAnalyzer to analyze the GreedyParallelPGStrategy with the MinimalParallelInput class as input.
 */
struct GreedyParallelPGStrategyPerfModule {

  typedef IMinimalParallelInputTraits::Task Task;
  typedef IMinimalParallelInputTraits::PE PE;

  /**
   * Creates the simulated input which the strategy analyzer will bind to the strategy.
   * @param argc The same argument count that is passed to the program.
   * @param argv The same argument values that are passed to the program.
   */
  MinimalParallelInput* createInput(int argc, char *argv[]);

  /**
   * Creates the simulated strategy which the strategy analyzer will simulate.
   * @param argc The same argument count that is passed to the program.
   * @param argv The same argument values that are passed to the program.
   */
  GreedyParallelPGStrategy* createStrategy(int argc, char *argv[]);

private:

  /**
   * Populates the task array for the simulated input with random and uniform distributed load values and sequential Ids.
   * @param tasksRef A reference to the already allocated array of tasks.
   * @param taskCount The number of tasks to be generated.
   * @param meanLoad The peak value of the normal distribution.
   * @param stdvLoad The standard deviation of the normal distribution.
   * @param seed A random seed that will be fed to a random engine, making it possible to reproduce the same distribution.
   */
  void populateTaskArray(Task *tasksRef, unsigned int taskCount, int meanLoad, int stdvLoad, int seed);

  /**
   * Populates the array of PEs for the simulated input with sequential id values.
   * @param PEsRef A reference to the already allocated array of PEs.
   * @param PECount The number of PEs to be generated.
   */
  void populatePEArray(PE *PEsRef, unsigned int PECount);

};