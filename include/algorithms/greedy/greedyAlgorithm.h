#pragma once

#include "concepts/greedyConcepts.h"

#include <system/traits.h>

/**
 * The struct that defines the generic greedy load balancer algorithm with compile-time defined data structures and types.
 * @type Task A type that serve as a task abstraction to the algorithm. This type must be a pointer.
 * @type PE A type that serve as a PE abtraction to the algorithm. This type must be a pointer
 * @type TaskMaxHeapComparator A type that has an operator() method for comparing a task to form a max heap.
 * @type PEMinHeapComparator A type that has an operator() method for comparing a PE to form a min heap.
 */
template<typename Task, typename PE, typename TaskMaxHeapComparator, typename PEMinHeapComparator>
struct GreedyStrategyAlgorithm {
  
  using MaxHeap = typename GreedyStrategyAlgorithmTraits<Task, PE, TaskMaxHeapComparator, PEMinHeapComparator>::MaxHeap;
  using MinHeap = typename GreedyStrategyAlgorithmTraits<Task, PE, TaskMaxHeapComparator, PEMinHeapComparator>::MinHeap;

  // This line is present in this class to present clear compile-time errors to developers and strategy users.
  static_assert(GreedyStrategyAlgorithmConcept<Task, PE, MaxHeap, MinHeap>::conforms(), "");

  /**
   * The function that will map tasks to PEs. The tasks will be mapped in th PEs parameter as it is passed as reference.
   * @param tasks a max heap of pointers to tasks.
   * @param PEs a min heap containing LoadBearers, interepreted as PEs in the system. This heap will contain the mapping after this function call.
   */
  void map(MaxHeap tasks, MinHeap PEs) const {
    auto maxHeapComparator = TaskMaxHeapComparator();
    auto minHeapComparator = PEMinHeapComparator();

    // Nothing to balance if PE heap is empty.
    if(PEs.empty())
      return;

    std::make_heap(tasks.begin(), tasks.end(), maxHeapComparator);
    std::make_heap(PEs.begin(), PEs.end(), minHeapComparator);

    // Main greedy strategy loop.
    while(!tasks.empty()) {
      auto task = tasks.front();
      auto _PE = PEs.front();

      std::pop_heap(tasks.begin(), tasks.end(), maxHeapComparator);
      std::pop_heap(PEs.begin(), PEs.end(), minHeapComparator);
      tasks.pop_back();
      PEs.pop_back();

      _PE->map(task->id(), task->load());
      
      PEs.push_back(_PE);
      std::push_heap(PEs.begin(), PEs.end(), minHeapComparator);
    }
  }
};