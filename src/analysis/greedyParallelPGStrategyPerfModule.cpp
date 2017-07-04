#include <analysis/greedyParallelPGStrategyPerfModule.h>

#include <iostream>
#include <random>

namespace GreedyPGPModule {
  typedef Traits<void>::Load Weight;

  /**
   * The penality function used in the performance module below.
   */
  const Weight penalityFunction(unsigned int size) {
    return 0;//size * size;
  }
}

MinimalParallelInput* GreedyParallelPGStrategyPerfModule::createInput(int argc, char *argv[]) {
  Task *tasks;
  PE *PEs;
  unsigned int PECount;
  unsigned int taskCount;

  if(argc < 7) {
    std::cout << "Correct execution of program: ./" << argv[0] << " {PE count} {Task Count} {Task Load Mean} {Task Load Std variation} {Random Seed} {Parallel Factor}" << std::endl;
    exit(0);
  }

  PECount = atoi(argv[1]);
  PEs = new PE[PECount];
  populatePEArray(PEs, PECount);

  taskCount = atoi(argv[2]);
  tasks = new Task[taskCount];
  populateTaskArray(tasks, taskCount, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

  return new MinimalParallelInput(PEs, tasks, PECount, taskCount);
}

GreedyParallelPGStrategy* GreedyParallelPGStrategyPerfModule::createStrategy(int argc, char *argv[]) {
  return new GreedyParallelPGStrategy(GreedyPGPModule::penalityFunction, atoi(argv[6]));
}

void GreedyParallelPGStrategyPerfModule::populateTaskArray(GreedyParallelPGStrategyPerfModule::Task *tasksRef, unsigned int taskCount, int meanLoad, int stdvLoad, int seed) {
  std::normal_distribution<float> normalDistribution(meanLoad, stdvLoad);
  std::default_random_engine randomEngine;
  randomEngine.seed(seed);

  for(unsigned int i = 0; i < taskCount; ++i) {
    tasksRef[i] = Task(i, normalDistribution(randomEngine));
  }
}

void GreedyParallelPGStrategyPerfModule::populatePEArray(GreedyParallelPGStrategyPerfModule::PE *PEsRef, unsigned int PECount) {
  for(unsigned int i = 0; i < PECount; ++i) {
    PEsRef[i] = PE(i);
  }
}