#include <gtest/gtest.h>

#include <algorithms/greedy/greedyAlgorithm.h>
#include <vector>
#include <map>
#include <iostream>

#include <strategies/adaptor/adaptorInterface.h>
#include <strategies/impl/greedy/greedyStrategy.h>

namespace GreedyAlogorithmTests {

#define GREEDY_STRATEGY_TEST_DEBUG true
#define GREEDY_ALGORITHM_TEST_DEBUG true

using LoadType = typename Traits<void>::Load;
using IdType = typename Traits<void>::Load;

/**
 * A basic structure that mocks a real environment's task/PE set for the greedy algorithm.
 */
struct LoadContainer {
  using Id = IdType;
  using Load = LoadType;

  std::vector<Id> id;
  std::vector<Load> load;
};

/**
 * A basic structure that serve the purpose of holding the partial map to tasks into PEs.
 */
struct DummyGreedyCallback : GreedyAlgorithmCallback<IdType, IdType> {
  using Id = IdType;

  std::map<Id, std::vector<Id> > mapping;
  LoadContainer *taskRef, *PERef;

  DummyGreedyCallback(LoadContainer *aTaskRef, LoadContainer *aPERef) {
    taskRef = aTaskRef;
    PERef = aPERef;
  }

  virtual ~DummyGreedyCallback() {}

  void algorithmMapped(const Id &task, const Id &toPE) {
    PERef->load[toPE] = taskRef->load[task] + PERef->load[toPE];

    auto it = mapping.find(toPE);

    if(it != mapping.end())
      it->second.push_back(task);
    else
      mapping[toPE] = std::vector<Id> {task};
  }
};

/**
 * This class is a fixture for the tests on the greedy algorithm class.
 */
class AlgorithmTest : public ::testing::Test {
public:
  using Id = IdType;
  using Load = LoadType;

  /**
   * A basic structure that satisfies the greedy's algorithm min heap comparator.
   */
  struct PECompare {
    LoadContainer *reference;

    PECompare(LoadContainer *aRef) : reference(aRef) {}

    inline bool operator ()(const Id &a, const Id &b) const {
      return reference->load[a] > reference->load[b];
    }
  };

  /**
   * A basic structure that satisfies the greedy's algorithm max heap comparator.
   */
  struct TaskCompare {
    LoadContainer *reference;

    TaskCompare(LoadContainer *aRef) : reference(aRef) {}

    inline bool operator ()(const Id &a, const Id &b) const {
      return reference->load[a] < reference->load[b];
    }
  };

  using Algorithm = GreedyStrategyAlgorithm<Id, Id, DummyGreedyCallback>;
  using MaxHeap = typename Algorithm::MaxHeap;
  using MinHeap = typename Algorithm::MinHeap;

  Algorithm algorithm;

  MinHeap minHeap;
  MaxHeap maxHeap;

  LoadContainer tasks, PEs;
  DummyGreedyCallback *callbackReceiver;
  
  TaskCompare *taskComparator;
  PECompare *PEComparator;

  /**
   * A proxy method to the tested feature in this fixture.
   */
  void callMap() {
    algorithm.map<TaskCompare, PECompare>(maxHeap, minHeap, callbackReceiver, *taskComparator, *PEComparator);
  }

  void SetUp() {
    callbackReceiver = new DummyGreedyCallback(&tasks, &PEs);
    taskComparator = new TaskCompare(&tasks);
    PEComparator = new PECompare(&PEs);
  }

  void TearDown() {
    delete callbackReceiver;
    delete taskComparator;
    delete PEComparator;
  }

};

/**
 * A dummy structure to mimic an input adaptor.
 */
class DummyAdaptor : public AdaptorInterface<> {
public:

  using Id = IdType;
  using Load = LoadType;

  LoadContainer PEs;
  LoadContainer tasks;

  inline const Load PELoad(const UInt &index) {
    return PEs.load[index];
  }

  inline void setPELoad(const UInt &index, const Load &load) {
    PEs.load[index] = load;
  }

  inline const Id PEId(const UInt &index) {
    return PEs.id[index];
  }

  inline const UInt PECount() {
    return PEs.id.size();
  }

  inline const Load taskLoad(const UInt &index) {
    return tasks.load[index];
  }

  inline void setTaskLoad(const UInt &index, const Load &load) {
    tasks.load[index] = load;
  }

  inline const Id taskId(const UInt &index) {
    return tasks.id[index];
  }

  inline const UInt taskCount() {
    return tasks.id.size();
  }

};


/**
 * This class is a fixture for the tests on the greedy strategy algorithm class.
 */
class StrategyTest : public ::testing::Test {
public:

  using Id = IdType;
  using Load = LoadType;

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
      adaptor.tasks.load.push_back(i);
      adaptor.tasks.id.push_back(i);
    }

    for(auto i = 0; i < 8; ++i) {
      adaptor.PEs.id.push_back(i);
      adaptor.PEs.load.push_back(0);
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
        totalLoad += adaptor.taskLoad(task);
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