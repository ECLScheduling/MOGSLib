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

template <>
struct TestTraits<PenalizedGraphAlgorithmTests> : TestTraits<void> {

  /**
   * The type of Penalized Graph Algorithm will be tested.
   */
  typedef PenalizedGraphAlgorithm<> PGAlgorithm;

  /**
   * The Weight type.
   */
  typedef PenalizedGraphAlgorithmTraits::Weight Weight;

  typedef EdgelessGraph Graph;

  typedef EdgelessVertex Vertex;

  /**
   * The penality function typedef.
   */
  typedef const Weight (*PenalityFunction)(const unsigned int);
};