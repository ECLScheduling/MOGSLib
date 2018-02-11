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
  for(UInt i = 0; i < ntasks; ++i)
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
  for(UInt i = 0; i < nPEs; ++i)
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
  UtilityAlgorithms::heapify<Load, UInt, true>(pe_map, pe_loads, nPEs, static_cast<UInt>(0));
}

};

}