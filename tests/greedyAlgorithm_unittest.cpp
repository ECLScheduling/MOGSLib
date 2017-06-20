#include <gtest/gtest.h>
#include <strategies/impl/greedy/greedyAlgorithm.h>

#include "helpers/test_traits.h"
#include "helpers/greedyAlgorithmHelpers.h"

class GreedyAlgorithmTest : public ::testing::Test {
public: 

  typedef TestTraits<GreedyAlgorithmTest>::DummyTask DummyTask;
  typedef TestTraits<GreedyAlgorithmTest>::DummyPE DummyPE;

  typedef GreedyStrategyAlgorithm<DummyTask, DummyPE> GreedyAlgorithm;
  typedef GreedyAlgorithm::MaxHeap MaxHeap;
  typedef GreedyAlgorithm::MinHeap MinHeap;

  GreedyAlgorithm algorithm;
  MaxHeap maxHeap;
  MinHeap minHeap;

  void map() {
    algorithm.map(maxHeap, minHeap);
  }
};

TEST_F(GreedyAlgorithmTest, emptyInput) {
  map();

  EXPECT_EQ(0, minHeap.size());
}

TEST_F(GreedyAlgorithmTest, oneTaskNoPE) {
  DummyTask task = 5;

  maxHeap.push(task);
  map();
  
  EXPECT_EQ(0, minHeap.size());
}

TEST_F(GreedyAlgorithmTest, onePENoTask) {
  minHeap.push(DummyPE());
  map();
  
  EXPECT_EQ(0, minHeap.top().sum());
}

TEST_F(GreedyAlgorithmTest, onePEOneTask) {
  DummyTask task = 5;

  minHeap.push(DummyPE());
  maxHeap.push(task);

  map();
  
  EXPECT_EQ(task, minHeap.top().sum());
}

TEST_F(GreedyAlgorithmTest, onePETwoTasks) {
  DummyTask task = 5, task2 = 8;

  minHeap.push(DummyPE());
  maxHeap.push(task);
  maxHeap.push(task2);

  map();
  
  EXPECT_EQ(task + task2, minHeap.top().sum());
}

TEST_F(GreedyAlgorithmTest, twoPETwoTasks) {
  DummyTask lesserTask = 5, greaterTask = 8;

  minHeap.push(DummyPE());
  minHeap.push(DummyPE());
  maxHeap.push(lesserTask);
  maxHeap.push(greaterTask);

  map();
  
  EXPECT_EQ(lesserTask, minHeap.top().sum());
  minHeap.pop();
  EXPECT_EQ(greaterTask, minHeap.top().sum());
}

TEST_F(GreedyAlgorithmTest, moreTasksThanPEs) {
  DummyTask lesserTask = 5, greaterTask = 8, mediumTask = 6;

  minHeap.push(DummyPE());
  minHeap.push(DummyPE());
  maxHeap.push(lesserTask);
  maxHeap.push(greaterTask);
  maxHeap.push(mediumTask);

  map();
  
  EXPECT_EQ(greaterTask, minHeap.top().sum());
  minHeap.pop();
  EXPECT_EQ(mediumTask + lesserTask, minHeap.top().sum());
}

TEST_F(GreedyAlgorithmTest, oneBigTask) {
  DummyTask bigTask = 20, task0 = 2, task1 = 3, task2 = 5;

  minHeap.push(DummyPE());
  minHeap.push(DummyPE());
  maxHeap.push(bigTask);
  maxHeap.push(task0);
  maxHeap.push(task1);
  maxHeap.push(task2);

  map();
  
  EXPECT_EQ(task0 + task1 + task2, minHeap.top().sum());
  minHeap.pop();
  EXPECT_EQ(bigTask, minHeap.top().sum());
}