#pragma once

#include <system/traits.h>

/**
 * The class that defines the penalized graph related algorithms with loose data definitions.
 * @type Weight The numeric type which will can describe the weight of a vertex and graph.
 */
template<typename Weight = Traits<void>::Load>
class PenalizedGraphAlgorithm {
public:

  typedef const Weight (*PenalityFunction)(const unsigned int size);

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
  PenalizedGraphAlgorithm(const Weight &zero, const PenalityFunction &penality) : zeroRef(zero), penalityFunction(penality) {}

  /**
   * Function to calculate the total weight of a graph, applying the penality function.
   * @param vWeightSum The sum of all the vertices' weight in the graph.
   * @param vSize The ammount of vertices in the graph.
   * @return The total weight of the graph accounting the penality function.
   */
  const Weight totalWeightGraph(const Weight &vWeightSum, const unsigned int &vSize) const;

  /**
   * Function to calculate the total weight of the graph resulting of an union of two graphs.
   * @param vSumA The sum of all the vertices' weight of the graph A.
   * @param vSumB The sum of all the vertices' weight of the graph B.
   * @param vSizeA The ammount of vertices in the graph A.
   * @param vSizeB The ammount of vertices in the graph B.
   * @return The weight of the graph union.
   */
  const Weight weightUnion(const Weight &vSumA, const Weight &vSumB, const unsigned int &vSizeA, const unsigned int &vSizeB) const;

  /**
   * Calculate the next weight value for a graph when it loses a vertex.
   * @param curWeight The current weight of the graph. This must account the penality function.
   * @param vSize The ammount of vertices in the graph.
   * @param vWeight The weight of the lost vertex.
   * @return the weight of the graph after it loses a vertex with the informed weight.
   */
  const Weight weightIncrementalLoseAVertex(const Weight &curWeight, const unsigned int &vSize, const Weight &vWeight) const;

  /**
   * Calculate the next weight value for a graph when it gains a vertex. This function must be called before the actual removal due to vertices' array size involved.
   * @param curWeight The current weight of the graph. This must account the penality function.
   * @param vSize The ammount of vertices in the graph.
   * @param vWeight The weight of the gained vertex.
   * @return the weight of the graph after it gains a vertex with the informed weight.
   */
  const Weight weightIncrementalGainAVertex(const Weight &curWeight, const unsigned int &vSize, const Weight &vWeight) const;

};

#include "penalizedGraphAlgorithm.ipp"