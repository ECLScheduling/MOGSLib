#include <strategies/impl/greedyPG/greedyPGStrategy.h>
#include "common/greedyPGStrategyTestFixture.h"

#include <iostream>
#include <queue>

// ###########################################
// Tests using the GreedyPGStrategyTest Fixture.
// ###########################################

/**
 * Fixture for testing the GreedyPGStrategy strategy.
 */
class GreedyPGStrategyTest : public GreedyPGStrategyFixture<GreedyPenalizedGraphStrategy> {
public:
  
  void createStrategy() {
    strategy = new GreedyPenalizedGraphStrategy(penalityFunction);
  }
};

TEST_F(GreedyPGStrategyTest, emptyTest) {
  PECount = 0;
  taskCount = 0;
  
  createStrategy();
  createInput();

  auto output = mapTasks();

  EXPECT_EQ(0, output.mappedPEs.size());
}

TEST_F(GreedyPGStrategyTest, noPEs) {
  PECount = 0;
  taskCount = 1;

  createStrategy();
  tasks = new Task(0,1);
  createInput();

  auto output = mapTasks();

  EXPECT_EQ(0, output.mappedPEs.size());
}

TEST_F(GreedyPGStrategyTest, noTasks) {
  PECount = 1;
  taskCount = 0;

  createStrategy();
  createInput();

  auto output = mapTasks();

  EXPECT_EQ(0, output.mappedPEs.size());
}

TEST_F(GreedyPGStrategyTest, realTest) {
  PECount = 2;
  taskCount = 16;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
  // After greedy: 0 [15, 12, 10, 9, 7, 4, 2, 1] + 1 [14, 13, 11, 8, 6, 5, 3, 0]
  std::vector<Load> expectedP0 = { 15, 12, 10, 9, 7, 4, 2, 1};
  std::vector<Load> expectedP1 = { 14, 13, 11, 8, 6, 5, 3, 0};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1}; 

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyPGStrategyTest, testWithMorePEs) {
  PECount = 4;
  taskCount = 16;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
  // After greedy: 0 [15, 8, 5, 2] + 1 [12, 11, 4, 3] + 2 [14, 9, 6, 1] + 3 [13, 10, 7, 0]
  std::vector<Load> expectedP0 = { 15, 8, 5, 2};
  std::vector<Load> expectedP1 = { 12, 11, 4, 3};
  std::vector<Load> expectedP2 = { 14, 9, 6, 1};
  std::vector<Load> expectedP3 = { 13, 10, 7, 0};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP2, expectedP1, expectedP3}; 

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyPGStrategyTest, testWithOddNumberOfTasksAndPEs) {
  PECount = 3;
  taskCount = 11;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10
  // After greedy: 0 [10, 5, 2] + 1 [9, 6, 3, 1, 0] + 2 [8, 7, 4]
  std::vector<Load> expectedP0 = { 10, 5, 2, 1};
  std::vector<Load> expectedP1 = { 9, 6, 3, 0};
  std::vector<Load> expectedP2 = { 8, 7, 4};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1, expectedP2}; 

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyPGStrategyTest, testWithSquarePenalityFunction) {
  PECount = 2;
  taskCount = 16;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
  // After greedy: 0 [15, 12, 10, 9, 7, 4, 2, 1] + 1 [14, 13, 11, 8, 6, 5, 3, 0]
  std::vector<Load> expectedP0 = { 15, 12, 10, 9, 7, 4, 2, 1};
  std::vector<Load> expectedP1 = { 14, 13, 11, 8, 6, 5, 3, 0};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1}; 

  Load expectedP0Load = 0;
  for(Load l : expectedP0)
    expectedP0Load += l;
  expectedP0Load += squarePenalityFunction(expectedP0.size());

  Load expectedP1Load = 0;
  for(Load l : expectedP1)
    expectedP1Load += l;
  expectedP1Load += squarePenalityFunction(expectedP1.size());

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}