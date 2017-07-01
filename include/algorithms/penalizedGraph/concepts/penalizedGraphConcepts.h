#pragma once

#include <system/static.h>

namespace PenalizedGraphConcepts {

HAS_MEMBER_MACRO(weight, has_weight)
HAS_MEMBER_MACRO(vertices, has_vertices)
HAS_MEMBER_MACRO(verticesSize, has_verticesSize)

/**
 * Struct to test wether a vertex type conforms to the expecified methods needed in the PenalizedGraphAlgorithm.
 */
template<typename Vertex>
struct VertexConcept {

  static constexpr bool conforms() {
    static_assert(has_weight<Vertex>::value, "'Vertex' type has no 'weight' method.");
    return true;
  }

};

/**
 * Struct to test wether a graph type conforms to the expecified methods needed in the PenalizedGraphAlgorithm.
 */
template<typename Graph>
struct GraphConcept {

  static constexpr bool conforms() {
    static_assert(has_weight<Graph>::value, "'Graph' type on 'PenalizedGraphAlgorithm' has no 'weight' method.");
    static_assert(has_vertices<Graph>::value, "'Graph' type on 'PenalizedGraphAlgorithm' has no 'vertices' method.");
    static_assert(has_verticesSize<Graph>::value, "'Graph' type on 'PenalizedGraphAlgorithm' has no 'verticesSize' method.");
    return true;
  }

};

/**
 * This class wraps all the rules that the types of PenalizedGraphAlgorithm must conform to.
 */
template<typename Graph, typename Vertex>
struct AlgorithmConcept {

  /**
   * This class is called to make all the needed static_asserts for this concept.
   */
  static constexpr bool conforms() {
    return GraphConcept<Graph>::conforms && VertexConcept<Vertex>::conforms;
  }
};

}