#include "fixtures/greedyFixtures.h"

namespace GreedyAlogorithmTests {

TEST_F(StrategyTest, simpleCase) {

  generateSimpleCase();

  mapTasks();

  printResult();
}

TEST_F(StrategyTest, PEIdsInvertedShouldWork) {

  for(auto i = 0; i < 50; ++i) {
    adaptor.taskLoads.push_back(i);
    adaptor.taskIds.push_back(i);
  }

  for(auto i = 0; i < 8; ++i) {
    adaptor.PEIds.push_back(8-i);
    adaptor.PELoads.push_back(0);
  }

  mapTasks();
  printResult();
}

TEST_F(StrategyTest, taskIdsInvertedShouldWork) {

  for(auto i = 0; i < 50; ++i) {
    adaptor.taskLoads.push_back(i);
    adaptor.taskIds.push_back(50-i);
  }

  for(auto i = 0; i < 8; ++i) {
    adaptor.PEIds.push_back(i);
    adaptor.PELoads.push_back(0);
  }

  mapTasks();

  printResult();
}

}