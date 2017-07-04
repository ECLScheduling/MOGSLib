#include <strategies/impl/greedyParallelPG/greedyParallelPGStrategy.h>

#include "common/greedyPGStrategyTestFixture.h"

// ###########################################
// Tests using the GreedyParallelPGStrategyTestNoPenality Fixture.
// ###########################################

/**
 * Fixture for testing the GreedyParallelPGStrategy strategy.
 */
class GreedyParallelPGStrategyTest : public GreedyPGStrategyFixture<GreedyParallelPGStrategy> {
public:
  unsigned int parallelFactor = 2;

  void createStrategy() {
    strategy = new GreedyParallelPGStrategy(penalityFunction, parallelFactor);
  }

};

TEST_F(GreedyParallelPGStrategyTest, emptyTest) {
  PECount = 0;
  taskCount = 0;
  
  createStrategy();
  createInput();

  auto output = mapTasks();

  EXPECT_EQ(0, output.mappedPEs.size());
}

TEST_F(GreedyParallelPGStrategyTest, noTasks) {
  PECount = 1;
  taskCount = 0;

  createStrategy();
  createInput();

  auto output = mapTasks();

  EXPECT_EQ(0, output.mappedPEs.size());
}

TEST_F(GreedyParallelPGStrategyTest, realTestParallelFactor2) {
  PECount = 2;
  taskCount = 16;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
  // After Greedy: 0 [15,12,10,9,7,4,2,1] + 1 [14,13,11,8,6,5,3]
  std::vector<Load> expectedP0 = { 15, 12, 10, 9, 7, 4, 2, 1};
  std::vector<Load> expectedP1 = { 14, 13, 11, 8, 6, 5, 3, 0};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1}; 

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyParallelPGStrategyTest, realTestParallelFactor4) {
  PECount = 2;
  taskCount = 16;
  parallelFactor = 4;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
  // Shards with PF = 4: [0,1,2,3,4,5,6,7] + [8,9,10,11,12,13,14,15]
  // After local Greedy PEs: (0[7,4,2,1] , 1[6,5,3,0]) + (0[15,12,10,9] , 1[14,13,11,8])
  // After reduction: 0 [15, 12, 10, 9, 7, 4, 2, 1] + 1 [14, 13, 11, 8, 6, 5, 3, 0]
  std::vector<Load> expectedP0 = { 15, 12, 10, 9, 7, 4, 2, 1};
  std::vector<Load> expectedP1 = { 14, 13, 11, 8, 6, 5, 3, 0};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1}; 

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyParallelPGStrategyTest, realTestPECount4) {
  PECount = 4;
  taskCount = 16;
  parallelFactor = 2;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
  // Shards with PF = 2: [0,1,2,3,4,5,6,7] + [8,9,10,11,12,13,14,15]
  // After local Greedy PEs: (0[7,0] , 1[6,1], 2[5,2], 3[4,3]) + (0[15,8] , 1[14,9], 2[13,10], 3[12,11])
  // After reduction: 0 [15, 8, 7, 0] + 1 [14, 9, 6, 1] + 2 [13, 10, 5, 2] + 3 [12, 11, 4, 3]
  std::vector<Load> expectedP0 = { 15, 8, 7, 0}; 
  std::vector<Load> expectedP1 = { 14, 9, 6, 1}; 
  std::vector<Load> expectedP2 = { 13, 10, 5, 2};
  std::vector<Load> expectedP3 = { 12, 11, 4, 3};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP3, expectedP1, expectedP2}; //NOTE: Order gets kind of randomized because of heap usage in internal code, but PEs still had the same values inside

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyParallelPGStrategyTest, worksWithOddNumberOfTasks) {
  PECount = 2;
  taskCount = 15;
  parallelFactor = 2;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
  // Shards with PF = 2: [0,1,2,3] + [4,5,6,7] + [8,9,10,11] + [12,13,14]
  // After local Greedy PEs: (0[3,0] , 1[2,1]) + (0[7,4] , 1[6,5]) + (0[11,8] , 1[10,9]) + (0[14] , 1[13,12])
  // After reduction: 0 [14,11,8,7,4,3,0] + 1 [13,12,10,9,6,5,2,1]
  std::vector<Load> expectedP0 = { 14, 11, 8, 7, 4, 3, 0}; 
  std::vector<Load> expectedP1 = { 13, 12, 10, 9, 6, 5, 2, 1};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1};

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyParallelPGStrategyTest, worksWithOddNumberOfShards) {
  PECount = 2;
  taskCount = 18; // Reducted to 3 then to 1 (in the reduction step).
  parallelFactor = 2;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17
  // Shards with PF = 2: [0,1,2,3] + [4,5,6,7] + [8,9,10,11] + [12,13,14,15] + [16,17] == 5 shards
  // After local Greedy PEs: (0[3,0] , 1[2,1]) + (0[7,4] , 1[6,5]) + (0[11,8] , 1[10,9]) + (0[15,12] , 1[14,13]) + (0[17] , 1[16])
  // After reduction: 0 [14,11,8,7,4,3,0] + 1 [13,12,10,9,6,5,2,1]
  std::vector<Load> expectedP0 = { 17, 15, 12, 11, 8, 7, 4, 3, 0}; 
  std::vector<Load> expectedP1 = { 16, 14, 13, 10, 9, 6, 5, 2, 1};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1};

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyParallelPGStrategyTest, worksWithMultipleReductedOddNumberOfShards) {
  PECount = 2;
  taskCount = 27; // Reducted to 7 then to 3 then to 1 (in the reduction step).
  parallelFactor = 1;

  createStrategy();
  createTasksWithIncrementalLoad();
  createInput();

  // Tasks: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26
  // Shards with PF = 1: [0,1], [2,3], [4,5], [6,7], [8,9], [10,11], [12,13], [14,15], [16,17], [18,19], [20,21], [22,23], [24,25], [26]
  // After reduction: 0 [26,25,23,21,19,17,15,13,11,9,7,5,3,1] + 1 [24,22,20,18,16,14,12,10,8,6,4,2,0]
  std::vector<Load> expectedP0 = {26,25,23,21,19,17,15,13,11,9,7,5,3,1}; 
  std::vector<Load> expectedP1 = {24,22,20,18,16,14,12,10,8,6,4,2,0};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1};

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyParallelPGStrategyTest, sortsTheInputBeforeMapping) {
  PECount = 2;
  taskCount = 8;
  parallelFactor = 2;

  createStrategy();
  createTasksWithDecrementingLoad();
  createInput();

  // Tasks: 1,2,3,4,5,6,8
  // Shards with PF = 2: [1,2,3,4] + [5,6,7,8]
  // After local Greedy PEs: (0[4,1] , 1[3,2]) + (0[8,5] , 1[7,6])
  // After reduction: 0 [8,5,4,1] + 1[7,6,3,2]
  std::vector<Load> expectedP0 = {8,5,4,1}; 
  std::vector<Load> expectedP1 = {7,6,3,2};

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1};

  compareOutput(expectedLoads, mapTasks().mappedPEs);
}

TEST_F(GreedyParallelPGStrategyTest, worksWithAPenalityFunction) {
  PECount = 2;
  taskCount = 8;
  parallelFactor = 2;
  penalityFunction = linearPenalityFunction;

  createStrategy();
  tasks = new Task[taskCount];

  for(unsigned int i = 0; i < taskCount; ++i) {
    tasks[i] = Task(i, i*2);
  }

  createInput();

  // Tasks: 0,2,4,6,8,10,12,14
  // Shards with PF = 2: [0,2,4,6] + [8,10,12,14]
  // After local Greedy PEs: (0[6,0] , 1[4,2]) + (0[14,8] , 1[12,10])
  // After reduction: 0 [14,8,6,0] + 1[12,10,4,2]
  // Total Weight = P0: 28 + 4 // P1: 28 + 4
  std::vector<Load> expectedP0 = {14,8,6,0}; 
  std::vector<Load> expectedP1 = {12,10,4,2};

  Load expectedP0Load = 28+4;
  Load expectedP1Load = 28+4;

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1};

  auto mappings = mapTasks().mappedPEs;
  compareOutput(expectedLoads, mappings);

  ASSERT_EQ(expectedP0Load, mappings[0]->load());
  ASSERT_EQ(expectedP1Load, mappings[1]->load());
}

TEST_F(GreedyParallelPGStrategyTest, worksWithASquarePenalityFunction) {
  PECount = 2;
  taskCount = 16;
  parallelFactor = 2;
  penalityFunction = squarePenalityFunction;

  createStrategy();
  tasks = new Task[taskCount];

  for(unsigned int i = 0; i < taskCount; ++i) {
    tasks[i] = Task(i, i*2);
  }

  createInput();

  // Tasks: 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30
  // Shards with PF = 2: [0,2,4,6] + [8,10,12,14] + [16,18,20,22] + [24,26,28,30]
  // After local Greedy PEs: (0[6,0] , 1[4,2]) + (0[14,8] , 1[12,10]) + (0[22,16] , 1[20,18]) + (0[30,24] , 1[28,26])
  // After reduction: 0 [30,24,22,16,14,8,6,0] + 1[28,26,20,18,12,10,4,2]
  std::vector<Load> expectedP0 = {30,24,22,16,14,8,6,0}; 
  std::vector<Load> expectedP1 = {28,26,20,18,12,10,4,2};

  Load expectedP0Load = 0;
  for(Load l : expectedP0)
    expectedP0Load += l;
  expectedP0Load += squarePenalityFunction(expectedP0.size());

  Load expectedP1Load = 0;
  for(Load l : expectedP1)
    expectedP1Load += l;
  expectedP1Load += squarePenalityFunction(expectedP1.size());

  std::vector< std::vector<Load> > expectedLoads = {expectedP0, expectedP1};

  auto mappings = mapTasks().mappedPEs;

  // for(auto pes : mappings) {
  //   std::cout << "PE" << pes->id << std::endl;
  //   for(auto task : pes->tasks) {
  //     std::cout << "\tTask " << task->id << ": " << task->load << std::endl;
  //   }
  // }

  compareOutput(expectedLoads, mappings);

  ASSERT_EQ(expectedP0Load, mappings[0]->load());
  ASSERT_EQ(expectedP1Load, mappings[1]->load());
}