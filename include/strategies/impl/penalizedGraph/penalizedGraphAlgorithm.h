#pragma once

#include "penalizedGraphConcepts.h"
#include <structures/edgelessGraph.h>
#include <system/traits.h>

/**
 * The class that defines the penalized graph related algorithms with loose data definitions.
 * @type Graph A type that contains a set of vertices and knows its size.
 * @details The Graph type must define a 'Vertex' and 'Weight' type.
 */
template<typename Graph = PenalizedGraphAlgorithmTraits::Graph>
class PenalizedGraphAlgorithm {
public:

  typedef typename Graph::Vertex Vertex;
  typedef typename Graph::Weight Weight;

  typedef const Weight (*PenalityFunction)(const unsigned int size);
  typedef const Vertex * const VerticesGroup;

  /**
   * A reference to a value correspondent to 0 weight.
   */
  const Weight zeroRef;

  /**
   * A penality function which will be applyied to the graph.
   */
  const PenalityFunction penalityFunction;

  /**
   * The constructor to the PenalizedGraphAlgorithm responsible to receive and initialize the default definitions of zero reference and penality function.
   * @param zero A reference to zero value in the Weight type.
   * @param penality The penality function which will be used to calculate the total weight of graphs.
   */
  PenalizedGraphAlgorithm(const Weight &zero, const PenalityFunction &penality) : zeroRef(zero), penalityFunction(penality) { static_assert(PenalizedGraphAlgorithmConcept<Graph, Vertex, Weight>::conforms(), ""); }

  /**
   * Function to sum the vertex weigth.
   * @param vertices An array of vertices to be summed together.
   * @param size The size of the vertices array.
   * @return The total sum of the vertice weights.
   */
  const Weight sumOfVertexWeight(VerticesGroup vertices, const unsigned int &size) const;

  /**
   * Function to calculate the total weight of a graph, which is an entity with a set of vertices.
   * @param graph The graph to have it's weight calculed.
   * @return The total weight of the graph accounting the penality function.
   */
  const Weight totalWeightGraph(Graph &graph) const;

  /**
   * Function to calculate the total weight of a graph resulting of an union of two graphs.
   * @param a The first graph in the union.
   * @param b The second graph in the union.
   * @return The weight of the graph union.
   */
  const Weight weightUnion(Graph &a, Graph &b) const;

  /**
   * Calculate the next weight value for a graph when it loses a vertex. This function must be called before the actual removal due to vertices' array size involved.
   * @param graph The graph which will lose a vertex.
   * @param vertexWeight The weight of the lost vertex.
   * @return the weight of the graph after it loses a vertex with the informed weight.
   */
  const Weight weightIncrementalLoseAVertex(Graph graph, const Weight &vertexWeight) const;

  /**
   * Calculate the next weight value for a graph when it gains a vertex. This function must be called before the actual removal due to vertices' array size involved.
   * @param graph The graph which will gain a vertex.
   * @param vertexWeight The weight of the gained vertex.
   * @return the weight of the graph after it gains a vertex with the informed weight.
   */
  const Weight weightIncrementalGainAVertex(Graph graph, const Weight &vertexWeight) const;

};

#include "penalizedGraphAlgorithm.ipp"