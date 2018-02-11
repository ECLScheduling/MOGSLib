#include <analysis/greedyPGStrategyPerfModule.h>

#include <iostream>
#include <random>

namespace GreedyPGModule {

typedef Traits<DefaultTypes>::Load Weight;

const Weight penalityFunction(unsigned int size) {
  return 0;
}

}

MinimalParallelInput* GreedyPGStrategyPerfModule::createInput(int argc, char *argv[]) {
  Task *tasks;
  PE *PEs;
  unsigned int PECount;
  unsigned int taskCount;

  if(argc < 7) {
    std::cout << "Correct execution of program: ./" << argv[0] << " {PE count} {Task count} {Distribution type} {Distribution param1} {Distribution param2} {Random Seed}" << std::endl;
    std::cout << "Possible values for {Distribution Type} and it's paramenters are:" << std::endl;
    std::cout << "\t0 -> Normal Distribution: Param1 = mean load, Param2 = standard deviation" << std::endl;
    std::cout << "\tAny -> Uniform Distribution: Param1 = min load, Param2 = max load" << std::endl;
    exit(0);
  }

  PECount = atoi(argv[1]);
  PEs = new PE[PECount];
  populatePEArray(PEs, PECount);

  taskCount = atoi(argv[2]);
  tasks = new Task[taskCount];

  if(atoi(argv[3]) == 0)
    populateTaskArrayNormalDist(tasks, taskCount, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
  else
    populateTaskArrayUniformDist(tasks, taskCount, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));

  return new MinimalParallelInput(PEs, tasks, PECount, taskCount);
}

GreedyPenalizedGraphStrategy* GreedyPGStrategyPerfModule::createStrategy(int argc, char *argv[]) {
  return new GreedyPenalizedGraphStrategy(GreedyPGModule::penalityFunction);
}

void GreedyPGStrategyPerfModule::populateTaskArrayNormalDist(GreedyPGStrategyPerfModule::Task *tasksRef, unsigned int taskCount, int meanLoad, int stdvLoad, int seed) {
  std::normal_distribution<float> normalDistribution(meanLoad, stdvLoad);
  std::default_random_engine randomEngine;
  randomEngine.seed(seed);

  for(unsigned int i = 0; i < taskCount; ++i) {
    tasksRef[i] = Task(i, normalDistribution(randomEngine));
  }
}

void GreedyPGStrategyPerfModule::populateTaskArrayUniformDist(GreedyPGStrategyPerfModule::Task *tasksRef, unsigned int taskCount, int min, int max, int seed) {
  std::uniform_int_distribution<int> uniformDistribution(min, max);
  std::default_random_engine randomEngine;
  randomEngine.seed(seed);

  for(unsigned int i = 0; i < taskCount; ++i) {
    tasksRef[i] = Task(i, uniformDistribution(randomEngine));
  }
}

void GreedyPGStrategyPerfModule::populatePEArray(GreedyPGStrategyPerfModule::PE *PEsRef, unsigned int PECount) {
  for(unsigned int i = 0; i < PECount; ++i) {
    PEsRef[i] = PE(i);
  }
}