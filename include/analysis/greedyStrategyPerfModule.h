#include <iostream>
#include <strategies/impl/greedy/greedyStrategy.h>
#include <strategies/input/naiveBasicInput.h>

/**
 * This struct is used by the StrategyAnalyzer to analyze the GreedyStrategy with the NaiveBasicOutput as input.
 */
struct GreedyStrategyPerfModule {

  typedef Traits<void>::Load Weight;
  typedef Traits<BasicInput>::SetOfId SetOfId;
  typedef Traits<BasicInput>::LoadMap LoadMap;

  NaiveBasicInput* createInput(int argc, char *argv[]) {
    SetOfId PEs;
    LoadMap tasks;

    if(argc < 2) {
      std::cout << "Correct execution of program: ./" << argv[0] << " {PE count} {Task Count}" << std::endl;
      exit(0);
    }

    for(auto i = 0; i < atoi(argv[1]); ++i)
      PEs.insert(i);
    for(int i = 0; i < atoi(argv[2]); ++i)
      tasks[i] = i*2;

    return new NaiveBasicInput(tasks, PEs);
  }

  GreedyStrategy<NaiveBasicInput>* createStrategy(int argc, char *argv[]) {
    return new GreedyStrategy<NaiveBasicInput>();
  }
};