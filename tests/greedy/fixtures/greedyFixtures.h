#include <gtest/gtest.h>

#include <algorithms/greedy/greedyAlgorithm.h>
#include <vector>
#include <iostream>

#include <strategies/input/adaptorInterface.h>
#include <strategies/impl/greedy/greedyStrategy.h>

namespace GreedyAlogorithmTests {

#define GREEDY_STRATEGY_TEST_DEBUG true
#define GREEDY_ALGORITHM_TEST_DEBUG true

/**
 * A basic structure that mocks a real environment's task for the greedy algorithm.
 */
class Task {
public:

  using Load = typename Traits<void>::Load;
  using Id = typename Traits<void>::Load;

  Id anId;
  Load aLoad;

  Task(const Id i, const Load l) {
    anId = i;
    aLoad = l;
  }

  inline Id id() {
    return anId;
  }

  inline Load load() {
    return aLoad;
  }

};

/**
 * A basic structure that mocks a real environment's PE for the greedy algorithm.
 */
class PE {
public:

  using Load = typename Traits<void>::Load;
  using Id = typename Traits<void>::Load;

  std::vector<Id> mappedTasks;
  Load aLoad;
  Id anId;

  PE(Id i) {
    anId = i;
    aLoad = 0;
  }

  void map(const Id &id, const Load &load) {
    mappedTasks.push_back(id);
    aLoad += load;
  }

  Load load() {
    return aLoad;
  }

};

/**
 * A basic structure that satisfies the greedy's algorithm max heap comparator.
 */
struct TaskCompare {
  inline bool operator ()(Task * const a, Task * const b) const {
    return a->aLoad < b->aLoad;
  }
};

/**
 * A basic structure that satisfies the greedy's algorithm min heap comparator.
 */
struct PECompare {
  inline bool operator ()(PE * const a, PE * const b) const {
    return a->aLoad > b->aLoad;
  }
};

/**
 * This class is a fixture for the tests on the greedy algorithm class.
 */
class AlgorithmTest : public ::testing::Test {
public:
  using Algorithm = GreedyStrategyAlgorithm<Task, PE, TaskCompare, PECompare>;
  using MaxHeap = typename Algorithm::MaxHeap;
  using MinHeap = typename Algorithm::MinHeap;

  Algorithm algorithm;
  MinHeap minHeap;
  MaxHeap maxHeap;

  void SetUp() {

  }

  void TearDown() {

  }

};

class DummyAdaptor : public AdaptorInterface<> {
public:

  std::vector<Load> PELoads, taskLoads;
  std::vector<Id> PEIds, taskIds;

  inline const Load PELoad(const UInt &index) const {
    return PELoads[index];
  }

  inline const Id PEId(const UInt &index) const {
    return PEIds[index];
  }

  inline const UInt PECount() const {
    return PEIds.size();
  }

  inline const Load taskLoad(const UInt &index) const {
    return taskLoads[index];
  }

  inline const Id taskId(const UInt &index) const {
    return taskIds[index];
  }

  inline const UInt taskCount() const {
    return taskLoads.size();
  }

};


/**
 * This class is a fixture for the tests on the greedy strategy algorithm class.
 */
class StrategyTest : public ::testing::Test {
public:
  using Strategy = GreedyStrategy<DummyAdaptor>;
  using Output = typename Strategy::Output;

  Strategy greedyStrategy;
  DummyAdaptor adaptor;

  Output result;

  void SetUp() {

  }

  void TearDown() {

  }

  /**
   * Generates a simple case where there are 8 PEs and 50 inputs with a increasing load.
   */
  void generateSimpleCase() {
    for(auto i = 0; i < 50; ++i) {
      adaptor.taskLoads.push_back(i);
      adaptor.taskIds.push_back(i);
    }

    for(auto i = 0; i < 8; ++i) {
      adaptor.PEIds.push_back(i);
      adaptor.PELoads.push_back(0);
    }
  }

  /**
   * Prints the output of the strategy
   */
  void printResult() {

    auto map = result.map;

    #if GREEDY_STRATEGY_TEST_DEBUG
    for (auto it= map.begin(); it!= map.end(); ++it) {
      auto totalLoad = 0;
      std::cout << "PE[" << it->first << "] with size (" << it->second.size() << "): "; 
      for(auto task : it->second) {
        totalLoad += adaptor.taskLoads[task];
        std::cout << task << " ";
      }
      std::cout << "(" << totalLoad << ")" <<std::endl;
    }
    #endif
  }

  void mapTasks() {
    result = greedyStrategy.mapTasks(adaptor);
  }

};

}