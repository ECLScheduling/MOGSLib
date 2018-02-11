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
 * @param A map of index to access the array with default values to be changed into a map in decreasing order.
 */
static void order_tasks(Load *loads, UInt ntasks, UInt *map) {
  UtilityAlgorithms::insertion_sort<Load, UInt, false>(map, loads, ntasks);
}

/**
 * @brief Creates a binary min-heap with the PEs by their load values.
 *
 * @param pe_loads The array of PE loads.
 * @param nPEs The amount of PEs.
 *
 * @param A map of index to access the array with default values to be changed into a binary heap.
 */
static void order_PEs(Load *pe_loads, UInt nPEs, UInt *map) {
  UtilityAlgorithms::make_heap<Load, UInt, true>(map, pe_loads, nPEs);
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