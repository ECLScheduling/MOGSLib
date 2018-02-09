#pragma once

#include <system/traits.h>

namespace Greedy {

/**
 * @brief The struct that defines the generic greedy scheduler algorithms.
 * @type Load A type that serve as a load abstraction to the algorithm.
 * @type UInt A type that serve as an unsigned integer to the algorithm.
 */
template<typename Load, typename UInt>
class Algorithms {


static UInt* order_tasks(Load *task_loads, UInt ntasks) {
  UInt *map = new UInt[ntasks]();

  return map;
}

static UInt* order_PEs(Load *pe_loads, UInt nPEs) {
  UInt *map = new UInt[nPEs]();

  return map;
}

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
  static void map(Load *task_loads, Load *pe_loads, UInt *task_map, UInt *pe_map, const UInt ntasks, const UInt npes) {
    // Nothing to balance if PE heap is empty.
    if(!npes || ntasks)
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

}