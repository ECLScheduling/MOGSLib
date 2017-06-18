#pragma once

template<typename Graph, typename Vertex, typename Weight>
class PenalizedGraphAlgorithm {
public:

  typedef const Weight (*PenalityFunction)(const unsigned int size);

  const Weight zeroRef;
  const PenalityFunction penalityFunction;

  PenalizedGraphAlgorithm(const Weight &zero, const PenalityFunction &penality) : zeroRef(zero), penalityFunction(penality) {}

  const Weight sumOfVertexWeight(Graph &graph) const {
    Weight weight = zeroRef;
    
    for(auto vertex : graph.vertices()) {
      weight += vertex.weight();
    }
    
    return weight;
  }

  const Weight totalWeightGraph(Graph &graph) const {
    Weight weight = sumOfVertexWeight(graph);

    weight += penalityFunction(graph.vertices().size());
    return weight;
  }

  const Weight totalWeightUnion(Graph &a, Graph &b) const {
    const Weight sum = totalWeightGraph(a) + totalWeightGraph(b);
    const Weight penality = penalityFunction(a.size() + b.size()) - penalityFunction(a.size()) - penalityFunction(b.size());
    
    return sum + penality; 
  }

};