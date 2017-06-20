#pragma once

#include "test_types.h"
#include <system/traits.h>

template<typename T>
struct TestTraits {};

template<>
struct TestTraits<GreedyAlgorithmTest> : TestTraits<void> {

  /**
   * Type that will server as a Task to test the Greedy Algorithm.
   */
  typedef unsigned int DummyTask;

  /**
   * Type that will serve as a PE to test the Greedy Algorithm.
   */
  typedef GreedyAlgorithmHelper::DummyPE DummyPE;
};

template<>
struct TestTraits<EdgelessGraphTests> : TestTraits<void> {

  struct TestTrait {
    typedef EdgelessVertex Vertex;
    typedef uint_fast32_t Weight;
    typedef uint_fast32_t Id;
    static const Weight zeroRef = 0;
  };

  /**
   * The default parameters for the EdgelessGraph testing.
   */
  typedef EdgelessGraph<TestTrait> Graph;

};

template<>
struct TestTraits<PenalizedGraphAlgorithmTests> : TestTraits<void> {

  /**
   * The graph type used in the tests, which is dependent on the Vertex type.
   */
  typedef EdgelessGraph<> Graph;

  /**
   * The vertex type that will be used in the Graph
   */
  typedef Graph::Vertex Vertex;

  /**
   * The Weight type is based of the Vertex type.
   */
  typedef Graph::Weight Weight;

  /**
   * The type of Penalized Graph Algorithm will be tested.
   */
  typedef PenalizedGraphAlgorithm<> PGAlgorithm;

  /**
   * The penality function typedef.
   */
  typedef const Weight (*PenalityFunction)(const unsigned int);
};