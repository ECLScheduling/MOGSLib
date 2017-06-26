#pragma once

#include <iostream>
#include <strategies/impl/penalizedGraph/greedyParallelPGStrategy.h>
#include <strategies/input/naiveBasicInput.h>

typedef Traits<void>::Load Weight;

namespace GreedyPGPModule {

const Weight squarePenality(unsigned int size) {
  return size * size;
}

}

/**
 * This struct is used by the StrategyAnalyzer to analyze the GreedyParallelPGStrategy with the NaiveBasicOutput as input.
 */
struct GreedyParallelPGStrategyPerfModule {

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
      PEs.push_back(i);
    for(int i = 0; i < atoi(argv[2]); ++i)
        tasks[i] = i*2;

    return new NaiveBasicInput(tasks, PEs);
  }

  GreedyParallelPGStrategy* createStrategy(int argc, char *argv[]) {
    return new GreedyParallelPGStrategy(GreedyPGPModule::squarePenality);
  }
};