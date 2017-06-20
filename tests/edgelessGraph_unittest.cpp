#include <gtest/gtest.h>
#include <memory>
#include <structures/edgelessGraph.h>

#include "helpers/test_traits.h"

typedef TestTraits<PenalizedGraphAlgorithmTests>::Weight Weight;

//########################################
// Fixture for the Edgeless Vertex Test.
//########################################

/**
 * This test fixture is for testing the EdgelessVertex functions, the most basic implementation for a vertex usable on PenalizedGraphAlgorithm.
 */
class EdgelessVertexTests : public ::testing::Test {
protected: 
  
  std::unique_ptr<EdgelessVertex> vertexA, vertexB;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  void createVertexAWithWeight(const Weight &weight) {
    vertexA = std::make_unique<EdgelessVertex>(weight);
  }

  void createVertexBWithWeight(const Weight &weight) {
    vertexB = std::make_unique<EdgelessVertex>(weight);
  }

};

TEST_F(EdgelessVertexTests, returnsTheCorrectWeight) {
  const Weight expected = 5;

  createVertexAWithWeight(expected);

  const Weight current = vertexA->weight();

  EXPECT_EQ(expected, current) << "Vertex should have weight " << expected << ", but had " << current << ".";
}

TEST_F(EdgelessVertexTests, lessThanOperatorTest) {
  const Weight greaterWeight = 7, lesserWeight = 5;

  createVertexAWithWeight(greaterWeight);
  createVertexBWithWeight(lesserWeight);

  const bool AIsGreater = (*vertexB) < (*vertexA);

  EXPECT_EQ(true, AIsGreater) << "Vertex A should be greater.";
}

TEST_F(EdgelessVertexTests, notLessThanOperatorTest) {
  const Weight greaterWeight = 7, lesserWeight = 5;

  createVertexAWithWeight(lesserWeight);
  createVertexBWithWeight(greaterWeight);

  const bool AIsGreater = (*vertexB) < (*vertexA);

  EXPECT_EQ(false, AIsGreater) << "Vertex B should be greater.";
}

//########################################
// Fixture for the Edgeless Graph Test.
//########################################

/**
 * This test fixture is for testing the EdgelessGraph functions, the most basic implementation for a graph usable on PenalizedGraphAlgorithm.
 */
class EdgelessGraphTests : public ::testing::Test {
protected: 
  
  EdgelessGraph graph;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }
};

TEST_F(EdgelessGraphTests, has0WeightWhenCreated) {
  auto expected = 0;
  auto actual = graph.weight();

  EXPECT_EQ(expected, actual) << "Graph should have " << expected << " weight on creation, but was " << actual << ".";
}

TEST_F(EdgelessGraphTests, has0WeightWhenNewVertexIsAdded) {
  auto expected = 0;
  auto nonZeroWeight = 3;

  graph.addVertex(EdgelessVertex(nonZeroWeight));

  auto actual = graph.weight();

  EXPECT_EQ(expected, graph.weight()) << "Graph should have " << expected << " weight even after adding a vertex, but was " << actual << ".";
}

TEST_F(EdgelessGraphTests, hasAnyWeightThatIsAssignedToItViaSetFuntion) {
  auto expected = 12;

  graph.setWeight(expected);

  auto actual = graph.weight();

  EXPECT_EQ(expected, actual) << "Graph should have " << expected << " weight after setWeight(), but was " << actual << ".";
}

TEST_F(EdgelessGraphTests, has0VerticesWhenCreated) {
  auto expected = 0;

  auto actual = graph.verticesSize();

  EXPECT_EQ(expected, actual) << "Graph should have " << expected << " vertices after creation, but was " << actual << ".";
}

TEST_F(EdgelessGraphTests, hasOneVertexAfterOneVertexIsAdded) {
  auto expected = 1;
  auto anyWeight = 9;

  graph.addVertex(EdgelessVertex(anyWeight));

  auto actual = graph.verticesSize();

  EXPECT_EQ(expected, actual) << "Graph should have " << expected << " vertices after creation, but was " << actual << ".";
}

TEST_F(EdgelessGraphTests, hasNVerticesAfterNVerticesAreAdded) {
  auto expected = 3;
  auto anyWeight = 9;

  for(auto i = 0; i < expected; ++i)
    graph.addVertex(EdgelessVertex(anyWeight));

  auto actual = graph.verticesSize();

  EXPECT_EQ(expected, actual) << "Graph should have " << expected << " vertices after creation, but was " << actual << ".";
}

TEST_F(EdgelessGraphTests, hasTheVerticesAccessibleAsAnArray) {
  auto verticesCount = 4;

  for(auto i = 0; i < verticesCount; ++i)
    graph.addVertex(EdgelessVertex(i));

  const EdgelessVertex * const vertices = graph.vertices();

  for(auto i = 0; i < verticesCount; ++i)
    EXPECT_EQ(i, vertices[i].weight());  
}