#pragma once

#include <system/traits.h>
#include <algorithms/utility.h>

namespace Greedy {

/**
 * @brief The struct that defines the generic greedy scheduler algorithms.
 *
 * @type Load A type that serve as a load abstraction to the algorithms.
 * @type UInt A type that serve as an unsigned integer to the algorithms.
 */
template<typename Load, typename UInt>
struct Algorithms {


/**
 * @brief Order the tasks that will be assigned by the Greedy Strategy by their load.
 *
 * @param loads The array of task loads.
 * @param ntasks The amount of tasks.
 *
 * @return A map of index to access the array in decreasing order.
 */
static UInt* order_tasks(Load *loads, UInt ntasks) {
  UInt *map = new UInt[ntasks]();
  for(UInt i = 0; i < n; ++i)
    map[i] = i;

  UtilityAlgorithms::insertion_sort<Load, UInt, false>(map, loads, ntasks);

  return map;
}

/**
 * @brief Creates a binary min-heap with the PEs by their load values.
 *
 * @param pe_loads The array of PE loads.
 * @param nPEs The amount of PEs.
 *
 * @return A map of the original indexes of the array that is now a binary heap.
 */
static UInt* order_PEs(Load *pe_loads, UInt nPEs) {
  UInt *map = new UInt[nPEs]();
  for(UInt i = 0; i < n; ++i)
    map[i] = i;

  UtilityAlgorithms::heap_sort<Load, UInt, true>(map, pe_loads, nPEs);

  return map;
}

/**
 * @brief Reorder the PEs of the binary heap after the first one have been updated.
 *
 * @param pe_loads The array of PE loads.
 * @param nPEs The amount of PEs.
 *
 * @return A map of the original indexes of the array that is now a binary heap.
 */
static void reorder_PEs(Load *pe_loads, UInt *pe_map, UInt nPEs) {
  UtilityAlgorithms::heapify<Load, UInt, true>(pe_map, pe_loads, nPES, static_cast<UInt>(0));
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