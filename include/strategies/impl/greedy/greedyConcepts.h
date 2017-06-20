#pragma once

#include <system/static.h>

/**
 * This class is used to formulate clear compile-time errors for when the template parameters doesn't implement the needed methods for the algorithms.
 */
template<typename Task, typename PE, typename MaxHeapStructure, typename MinHeapStructure>
struct GreedyStrategyAlgorithmConcept {

  HAS_MEMBER_MACRO(empty, has_empty)
  HAS_MEMBER_MACRO(top, has_top)
  HAS_MEMBER_MACRO(pop, has_pop)
  HAS_MEMBER_MACRO(push, has_push)
  HAS_MEMBER_MACRO(mapTask, has_mapTask)

  /**
   * This class is called to make all the needed static_asserts for this concept.
   */
  static constexpr bool conforms() {
    static_assert(has_mapTask<PE>::value, "'PE' type on 'GreedyLoadBalancerAlgorithm' has no 'mapTask' method.");

    static_assert(has_empty<MaxHeapStructure>::value, "'MaxHeapStructure' type on 'GreedyLoadBalancerAlgorithm' has no 'empty' method.");
    static_assert(has_top<MaxHeapStructure>::value, "'MaxHeapStructure' type on 'GreedyLoadBalancerAlgorithm' has no 'top' method.");
    static_assert(has_pop<MaxHeapStructure>::value, "'MaxHeapStructure' type on 'GreedyLoadBalancerAlgorithm' has no 'pop' method.");

    static_assert(has_empty<MinHeapStructure>::value, "'MinHeapStructure' type on 'GreedyLoadBalancerAlgorithm' has no 'empty' method.");
    static_assert(has_top<MinHeapStructure>::value, "'MinHeapStructure' type on 'GreedyLoadBalancerAlgorithm' has no 'top' method.");
    static_assert(has_pop<MinHeapStructure>::value, "'MinHeapStructure' type on 'GreedyLoadBalancerAlgorithm' has no 'pop' method.");
    
    return true;
  }

};
