#pragma once

#include <system/static.h>

/**
 * This class is used to formulate clear compile-time errors for when the template parameters doesn't implement the needed methods for the algorithms.
 */
template<typename Task, typename PE, typename MaxHeap, typename MinHeap>
struct GreedyStrategyAlgorithmConcept {

  HAS_MEMBER_MACRO(map, has_map)

  HAS_MEMBER_MACRO(id, has_id)
  HAS_MEMBER_MACRO(load, has_load)

  HAS_MEMBER_MACRO(pop_back, has_pop_back)

  /**
   * This class is called to make all the needed static_asserts for this concept.
   */
  static constexpr bool conforms() {
    static_assert(has_map<PE>::value, "'PE' type on 'GreedyStrategyAlgorithm' has no 'map' method.");

    static_assert(has_id<Task>::value, "'Task' type on 'GreedyStrategyAlgorithm' has no 'id' method.");
    static_assert(has_load<Task>::value, "'Task' type on 'GreedyStrategyAlgorithm' has no 'load' method.");

    static_assert(has_pop_back<MaxHeap>::value, "'MaxHeap' type on 'GreedyStrategyAlgorithm' has no 'pop_back' method.");
    static_assert(has_pop_back<MinHeap>::value, "'MinHeap' type on 'GreedyStrategyAlgorithm' has no 'pop_back' method.");
    return true;
  }

};
