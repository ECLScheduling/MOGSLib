#include "fixtures/greedyFixtures.h"

namespace GreedyAlogorithmTests {

TEST_F(StrategyTest, simpleCase) {

  generateSimpleCase();

  mapTasks();

  printResult();
}

TEST_F(StrategyTest, PEIdsInvertedShouldWork) {

  for(auto i = 0; i < 50; ++i) {
    adaptor.tasks.load.push_back(i);
    adaptor.tasks.id.push_back(i);
  }

  for(auto i = 0; i < 8; ++i) {
    adaptor.PEs.id.push_back(8-i);
    adaptor.PEs.load.push_back(0);
  }

  mapTasks();
  printResult();
}

TEST_F(StrategyTest, taskIdsInvertedShouldWork) {

  for(auto i = 0; i < 50; ++i) {
    adaptor.tasks.load.push_back(i);
    adaptor.tasks.id.push_back(50-i);
  }

  for(auto i = 0; i < 8; ++i) {
    adaptor.PEs.id.push_back(i);
    adaptor.PEs.load.push_back(0);
  }

  mapTasks();

  printResult();
}

}