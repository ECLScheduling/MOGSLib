#pragma once

#include "greedyConcepts.h"

#include <system/traits.h>

/**
 * The struct that defines the generic greedy load balancer algorithm with compile-time defined data structures and types.
 * @type Task A type that serve as a task abstraction to the algorithm.
 * @type PE A type that serve as a PE abtraction to the algorithm.
 * @type MaxHeapTemplate A type that will be serve as a Max Heap for the greedy algorithm. Defaults to GreedyDefaultDataStructure::MaxHeap
 * @type MinHeapTemplate A type that will be serve as a Min Heap for the greedy algorithm. Defaults to GreedyDefaultDataStructure::MinHeap
 */
template<typename Task, typename PE, typename MaxHeapTemplate = typename GreedyStrategyAlgorithmTraits<Task, PE>::MaxHeap, typename MinHeapTemplate = typename GreedyStrategyAlgorithmTraits<Task, PE>::MinHeap>
struct GreedyStrategyAlgorithm {
  
  typedef typename GreedyStrategyAlgorithmTraits<Task, PE>::Id Id;
  typedef typename GreedyStrategyAlgorithmTraits<Task, PE>::Load Load;
  typedef MaxHeapTemplate MaxHeap;
  typedef MinHeapTemplate MinHeap;

  // This line is present in this class to present clear compile-time errors to developers and users.
  static_assert(GreedyStrategyAlgorithmConcept<Task, PE, MaxHeap, MinHeap>::conforms(), "");

  /**
   * The function that will map tasks to PEs. The tasks will be mapped in th PEs parameter as it is passed as reference.
   * @param tasks a max heap containing LoadBearers, interepreted as tasks in the system.
   * @param PEs a min heap containing LoadBearers, interepreted as PEs in the system. This heap will contain the mapping after this function call.
   */
  void map(MaxHeap tasks, MinHeap &PEs) const {

    // Doesnt make sense to balance a load to an empty set of processing units.
    if(PEs.empty() || tasks.empty())
      return;

    // Main greedy strategy loop.
    while(!tasks.empty()) {
      const Task task = tasks.top();
      PE _PE = PEs.top();

      tasks.pop();
      PEs.pop();

      _PE.mapTask(task);
      PEs.push(_PE);
    }
  }
};