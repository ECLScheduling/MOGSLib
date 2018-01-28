#pragma once

#include <system/traits.h>

/**
 * @brief The default definition of the GreedyAlgorithm callback class.
 * @type Task The type definition of the task that a greedy algorithm uses.
 * @type PE the type definition of the PE that a greedy algorithm uses.
 */
template<typename Task, typename PE>
class GreedyAlgorithmCallback {
public:
  
  /**
   * This method is called everytime the greedy algorithm maps a task to a PE.
   * @details Inside this method the load of the task must be adjusted to match it's addition to the PE's mapped tasks.
   * @param task The task that has been mapped.
   * @param toPE The PE that has received the task.
   */
  virtual void algorithmMapped(const Task &task, const PE &toPE) = 0;
};

/**
 * @brief The struct that defines the generic greedy load balancer algorithm with compile-time defined data structures and types.
 * @type Task A type that serve as a task abstraction to the algorithm. This type must be a pointer.
 * @type PE A type that serve as a PE abtraction to the algorithm. This type must be a pointer
 * @type CallbackType A type that has the method algorithmMapped, that will be called everytime a task is mapped to a PE in the algorithm.
 */
template<typename Task, typename PE, typename Callback>
struct GreedyStrategyAlgorithm {
  
  using MaxHeap = typename GreedyStrategyAlgorithmTraits<Task, PE>::MaxHeap;
  using MinHeap = typename GreedyStrategyAlgorithmTraits<Task, PE>::MinHeap;

  /**
   * The function that will map tasks to PEs. The tasks will be mapped in th PEs parameter as it is passed as reference.
   * @type MaxHeapCmp A max-heap comparator type for the greedy algorithm.
   * @type MinHeapCmp A min-heap comparator type for the greedy algorithm.
   * @param tasks A max heap of pointers to tasks.
   * @param PEs A min heap containing LoadBearers, interepreted as PEs in the system. This heap will contain the mapping after this function call.
   * @param callback A callback class that will receive calls when a task is mapped.
   * @param maxHeapComparator An instance of a class that can compare two tasks in regards to their load.
   * @param minHeapComparator An instance of a class that can compare two PEs in regards to their load.
   */
  template<typename MaxHeapCmp, typename MinHeapCmp>
  void map(MaxHeap tasks, MinHeap PEs, Callback *callback, const MaxHeapCmp &maxHeapComparator, const MinHeapCmp &minHeapComparator) const {
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

      // Task has been mapped and the callback method must adjust the load of the PE.
      callback->algorithmMapped(task, _PE);
      
      PEs.push_back(_PE);
      std::push_heap(PEs.begin(), PEs.end(), minHeapComparator);
    }
  }
};