#pragma once

#include <queue>
#include <system/traits.h>
#include <map>

/**
 * A struct that defines the default data structures for the GreedyLoadBalancerAlgorithm.
 * @type Task A type that serve as a task abstraction to the algorithm.
 * @type PE A type that serve as a PE abtraction to the algorithm.
 */
template<typename Task, typename PE>
struct GreedyDefaultDataStructure {
  
  /**
   * Internal Helper struct to be used as the max-heap comparator.
   */
  struct MaxHeapComparator {
    inline bool operator ()(const Task &a, const Task &b) const {
      return a.load < b.load;
    }
  };

  /**
   * Internal Helper struct to be used as the min-heap comparator.
   */
  struct MinHeapComparator {
    inline bool operator ()(const PE &a, const PE &b) const {
      return a.load > b.load;
    }
  };

  typedef std::priority_queue<Task, std::vector<LoadBearer>, MaxHeapComparator > MaxHeap;
  typedef std::priority_queue<PE, std::vector<LoadBearer>, MinHeapComparator > MinHeap;
};

/**
 * The struct that defines the generic greedy load balancer algorithm with compile-time defined data structures and types.
 * @type Task A type that serve as a task abstraction to the algorithm.
 * @type PE A type that serve as a PE abtraction to the algorithm.
 * @type MaxHeapStructure A type that will be serve as a Max Heap for the greedy algorithm. Defaults to GreedyDefaultDataStructure::MaxHeap
 * @type MinHeapStructure A type that will be serve as a Min Heap for the greedy algorithm. Defaults to GreedyDefaultDataStructure::MinHeap
 */
template<typename Task, typename PE, typename MaxHeapStructure = GreedyDefaultDataStructure<Task, PE>::MaxHeap, typename MinHeapStructure = GreedyDefaultDataStructure<Task, PE>::MinHeap>
struct GreedyLoadBalancerAlgorithm {
  typedef Traits<MigrationElement>::Id Id;
  typedef std::map<Id,Id> IdMap;
  typedef Traits<MigrationElement>::Load Load;

  /**
   * The function that will map tasks to PEs. The tasks will be mapped in th PEs parameter as it is passed as reference.
   * @param tasks a max heap containing LoadBearers, interepreted as tasks in the system.
   * @param PEs a min heap containing LoadBearers, interepreted as PEs in the system. This heap will contain the mapping after this function call.
   */
  void map(MaxHeapStructure tasks, MinHeapStructure &PEs) const {

    // Doesnt make sense to balance a load to an empty set of processing units.
    if(PEs.empty() || tasks.empty())
      return;

    // Main greedy strategy loop.
    while(!tasks.empty()) {
      const LoadBearer task = tasks.top();
      const LoadBearer _PE = PEs.top();

      tasks.pop();
      PEs.pop();

      _PE.mapTask(task);
      PEs.push(_PE);
    }
  }
};