#pragma once

#include <system/static.h>

/**
 * This class is used to formulate clear compile-time errors for when the template parameters doesn't implement the needed methods for the algorithms.
 */
template<typename Graph, typename Vertex, typename Weight>
struct PenalizedGraphAlgorithmConcept {
  HAS_MEMBER_MACRO(weight, has_weight)
  HAS_MEMBER_MACRO(vertices, has_vertices)
  HAS_MEMBER_MACRO(verticesSize, has_verticesSize)


  /**
   * This class is called to make all the needed static_asserts for this concept.
   */
  static constexpr bool conforms() {
    static_assert(has_weight<Graph>::value, "'Graph' type on 'PenalizedGraphAlgorithm' has no 'weight' method.");
    static_assert(has_vertices<Graph>::value, "'Graph' type on 'PenalizedGraphAlgorithm' has no 'vertices' method.");
    static_assert(has_verticesSize<Graph>::value, "'Graph' type on 'PenalizedGraphAlgorithm' has no 'verticesSize' method.");

    static_assert(has_weight<Vertex>::value, "'Vertex' type on 'PenalizedGraphAlgorithm' has no 'weight' method.");
    return true;
  }
};