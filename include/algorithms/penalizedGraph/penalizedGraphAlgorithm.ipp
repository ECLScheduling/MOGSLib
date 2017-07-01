// #############################################
// Implementation of the PenalizedGraphAlgorithm template methods.
// #############################################


template<typename Graph>
const typename PenalizedGraphAlgorithm<Graph>::Weight PenalizedGraphAlgorithm<Graph>::sumOfVertexWeight(typename PenalizedGraphAlgorithm<Graph>::VerticesGroup vertices, const unsigned int &size) const {
  Weight weight = zeroRef;
  
  for(unsigned int i = 0; i < size; ++i) {
    weight += vertices[i].weight();
  }
    
  return weight;
}

template<typename Graph>
const typename PenalizedGraphAlgorithm<Graph>::Weight PenalizedGraphAlgorithm<Graph>::totalWeightGraph(Graph &graph) const {
  const unsigned int size = graph.verticesSize();

  return sumOfVertexWeight(graph.vertices(), size) + penalityFunction(size);
}

template<typename Graph>
const typename PenalizedGraphAlgorithm<Graph>::Weight PenalizedGraphAlgorithm<Graph>::weightUnion(Graph &a, Graph &b) const {
  const unsigned int sizeA = a.verticesSize();
  const unsigned int sizeB = b.verticesSize();

  const Weight sum = totalWeightGraph(a) + totalWeightGraph(b);
  const Weight penality = penalityFunction(sizeA + sizeB) - penalityFunction(sizeA) - penalityFunction(sizeB);
    
  return sum + penality; 
}

template<typename Graph>
const typename PenalizedGraphAlgorithm<Graph>::Weight PenalizedGraphAlgorithm<Graph>::weightIncrementalLoseAVertex(Graph graph, const typename PenalizedGraphAlgorithm<Graph>::Weight &vertexWeight) const {
  Weight weight;

  weight = graph.weight() - vertexWeight - penalityFunction(graph.verticesSize()) + penalityFunction(graph.verticesSize()-1);
     
  return weight;
}

template<typename Graph>
const typename PenalizedGraphAlgorithm<Graph>::Weight PenalizedGraphAlgorithm<Graph>::weightIncrementalGainAVertex(Graph graph, const typename PenalizedGraphAlgorithm<Graph>::Weight &vertexWeight) const {
  Weight weight;

  weight = graph.weight() + vertexWeight - penalityFunction(graph.verticesSize()) + penalityFunction(graph.verticesSize()+1);
     
  return weight;
}