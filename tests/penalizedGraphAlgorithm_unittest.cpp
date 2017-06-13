#include <gtest/gtest.h>

#include <lb/impl/penalizedGraph/penalizedGraphAlgorithm.h>
#include <lb/impl/penalizedGraph/edgelessGraph.h>
#include <memory>

typedef EdgelessGraph::Weight Weight;

const Weight squarePenality(const unsigned int size) {
  return size * size;
}

const Weight linearPenality(const unsigned int size) {
  return size;
}

const Weight noPenality(const unsigned int size) {
  return 0;
}

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

/**
 * This test fixture is for testing the penalized graphs algorithms with different inputs.
 */
class PenalizedGraphAlgorithmTests : public ::testing::Test {
protected: 
  typedef PenalizedGraphAlgorithm<EdgelessGraph, EdgelessVertex, Weight> PGAlgorithm;

  std::unique_ptr<PGAlgorithm> algorithm;
  EdgelessVertex *vertices, *verticesB;
  EdgelessGraph graph, graphB;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

  void createWithSquarePenality() {
    algorithm = std::make_unique<PGAlgorithm>(0, squarePenality);
  }

  void createWithLinearPenality() {
    algorithm = std::make_unique<PGAlgorithm>(0, linearPenality);
  }

  void createWithNoPenality() {
    algorithm = std::make_unique<PGAlgorithm>(0, noPenality); 
  }

};

TEST_F(PenalizedGraphAlgorithmTests, sumOfEmptyVerticesSetShouldBe0) {
  auto expected = 0;
  auto actual = 0;

  createWithNoPenality();
  actual = algorithm->sumOfVertexWeight(vertices, 0);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for vertice set sum.";
}

TEST_F(PenalizedGraphAlgorithmTests, sumOfOneVertexShouldBeItsVertexWeight) {
  auto expected = 86;
  auto actual = 0;

  createWithNoPenality();

  vertices = new EdgelessVertex[1];
  vertices[0] = expected;
  actual = algorithm->sumOfVertexWeight(vertices, 1);

  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for vertice set sum.";

  delete vertices;
}

TEST_F(PenalizedGraphAlgorithmTests, sumOfNVertexShouldBeCorrect) {
  auto expectedSum = 10;
  auto verticeCount = 5;
  auto actual = 0;

  createWithNoPenality();

  vertices = new EdgelessVertex[verticeCount];
  for(auto i = 0; i < verticeCount; ++i)
    vertices[i] = expectedSum/verticeCount;

  actual = algorithm->sumOfVertexWeight(vertices, verticeCount);

  EXPECT_EQ(expectedSum, actual) << "Algorithm should have returned " << expectedSum << " for vertice set sum.";

  delete[] vertices;
}

TEST_F(PenalizedGraphAlgorithmTests, totalWeightOfEmptyGraphIs0) {
  auto expected = 0;
  auto actual = 0;

  createWithNoPenality();
  actual = algorithm->totalWeightGraph(graph);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total graph weight.";
}

TEST_F(PenalizedGraphAlgorithmTests, shouldAccountPenalityFunctionEvenOnUnitaryGraphs) {
  auto expected = 0;
  auto actual = 0;
  auto vertexWeight = 10;

  graph.addVertex(vertexWeight);

  createWithNoPenality();
  expected = vertexWeight + noPenality(1);
  actual = algorithm->totalWeightGraph(graph);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total graph weight with no penality function.";

  createWithSquarePenality();
  expected = vertexWeight + squarePenality(1);
  actual = algorithm->totalWeightGraph(graph);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total graph weight with square penality function.";

  createWithLinearPenality();
  expected = vertexWeight + linearPenality(1);
  actual = algorithm->totalWeightGraph(graph);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total graph weight with linear penality function.";
}

TEST_F(PenalizedGraphAlgorithmTests, shouldAccountPenalityFunctionOnGraphsWithNVertices) {
  auto expected = 0;
  auto actual = 0;
  auto verticesCount = 5;
  auto vertexWeightSum = 0;

  for(auto i = 0; i < verticesCount; ++i) {
    graph.addVertex(i);
    vertexWeightSum += i;
  }
  

  createWithNoPenality();
  expected = vertexWeightSum + noPenality(verticesCount);
  actual = algorithm->totalWeightGraph(graph);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total graph weight with no penality function.";

  createWithSquarePenality();
  expected = vertexWeightSum + squarePenality(verticesCount);
  actual = algorithm->totalWeightGraph(graph);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total graph weight with square penality function.";

  createWithLinearPenality();
  expected = vertexWeightSum + linearPenality(verticesCount);
  actual = algorithm->totalWeightGraph(graph);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total graph weight with linear penality function.";
}

TEST_F(PenalizedGraphAlgorithmTests, unionOfTwoGraphsHasCombinedOnNoPenaltyFunction) {
  auto verticesACount = 5;
  auto verticesBCount = 4; 
  auto verticesASum = 20; // Sum/Count Divisible number for the sake of automatic testing
  auto verticesBSum = 40; // Sum/Count Divisible number for the sake of automatic testing

  for(auto i = 0; i < verticesACount; ++i)
    graph.addVertex(verticesASum/verticesACount);
  for(auto i = 0; i < verticesBCount; ++i)
    graphB.addVertex(verticesBSum/verticesBCount);

  createWithNoPenality();
  auto expected = verticesASum + verticesBSum;
  auto actual = algorithm->weightUnion(graph, graphB);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total union weight, but returned " << actual << " instead.";
}

TEST_F(PenalizedGraphAlgorithmTests, unionOfTwoGraphsAppliesPenalityFunctionCorrectly) {
  auto verticesACount = 5;
  auto verticesBCount = 4; 
  auto verticesASum = 20; // Sum/Count Divisible number for the sake of automatic testing
  auto verticesBSum = 40; // Sum/Count Divisible number for the sake of automatic testing

  EdgelessGraph unifiedGraph;

  for(auto i = 0; i < verticesACount; ++i) {
    graph.addVertex(verticesASum/verticesACount);
    unifiedGraph.addVertex(verticesASum/verticesACount);
  }

  for(auto i = 0; i < verticesBCount; ++i) {
    graphB.addVertex(verticesBSum/verticesBCount);
    unifiedGraph.addVertex(verticesBSum/verticesBCount);
  }

  createWithLinearPenality();
  auto expected = algorithm->totalWeightGraph(unifiedGraph);
  auto actual = algorithm->weightUnion(graph, graphB);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total union weight, but returned " << actual << " instead.";

  createWithSquarePenality();
  expected = algorithm->totalWeightGraph(unifiedGraph);
  actual = algorithm->weightUnion(graph, graphB);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for total union weight, but returned " << actual << " instead.";
}

TEST_F(PenalizedGraphAlgorithmTests, iterativeRemovalOfVertexWeightCalculation) {
  auto verticesCount = 10;
  auto lastVerticeWeight = verticesCount-1;

  EdgelessGraph postRemovalGraph;

  for(auto i = 0; i < verticesCount; ++i) {
    graph.addVertex(i);
  }
  for(auto i = 0; i < verticesCount-1; ++i) {
    postRemovalGraph.addVertex(i);
  }

  createWithNoPenality();
  graph.setWeight(algorithm->totalWeightGraph(graph));

  auto expected = algorithm->totalWeightGraph(postRemovalGraph);
  auto actual = algorithm->weightIncrementalLoseAVertex(graph, lastVerticeWeight);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for incremental weight after removing a vertex using no penality, but returned " << actual << " instead.";

  createWithLinearPenality();
  graph.setWeight(algorithm->totalWeightGraph(graph));
  
  expected = algorithm->totalWeightGraph(postRemovalGraph);
  actual = algorithm->weightIncrementalLoseAVertex(graph, lastVerticeWeight);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for incremental weight after removing a vertex using linear penality, but returned " << actual << " instead.";

  createWithSquarePenality();
  graph.setWeight(algorithm->totalWeightGraph(graph));
  
  expected = algorithm->totalWeightGraph(postRemovalGraph);
  actual = algorithm->weightIncrementalLoseAVertex(graph, lastVerticeWeight);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for incremental weight after removing a vertex using square penality, but returned " << actual << " instead.";
}

TEST_F(PenalizedGraphAlgorithmTests, iterativeAdditionOfVertexWeightCalculation) {
  auto verticesCount = 10;
  auto lastVerticeWeight = verticesCount;

  EdgelessGraph postAdditionGraph;

  for(auto i = 0; i < verticesCount; ++i) {
    graph.addVertex(i);
  }
  for(auto i = 0; i < verticesCount+1; ++i) {
    postAdditionGraph.addVertex(i);
  }

  createWithNoPenality();
  graph.setWeight(algorithm->totalWeightGraph(graph));

  auto expected = algorithm->totalWeightGraph(postAdditionGraph);
  auto actual = algorithm->weightIncrementalGainAVertex(graph, lastVerticeWeight);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for incremental weight after adding a vertex using no penality, but returned " << actual << " instead.";

  createWithLinearPenality();
  graph.setWeight(algorithm->totalWeightGraph(graph));
  
  expected = algorithm->totalWeightGraph(postAdditionGraph);
  actual = algorithm->weightIncrementalGainAVertex(graph, lastVerticeWeight);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for incremental weight after adding a vertex using linear penality, but returned " << actual << " instead.";

  createWithSquarePenality();
  graph.setWeight(algorithm->totalWeightGraph(graph));
  
  expected = algorithm->totalWeightGraph(postAdditionGraph);
  actual = algorithm->weightIncrementalGainAVertex(graph, lastVerticeWeight);
  EXPECT_EQ(expected, actual) << "Algorithm should have returned " << expected << " for incremental weight after adding a vertex using square penality, but returned " << actual << " instead.";
}