#include <lb/impl/penalizedGraph/PenalizedGraphAlgorithm.h>
#include <deque>
#include <iostream>

typedef int Weight;

class VertexImpl {
public:

  const Weight vWeight;

  VertexImpl(const Weight &aWeight) : vWeight(aWeight) {}

  const Weight weight() const {
    return vWeight;
  }

  const bool operator <(const VertexImpl &v) const {
    return vWeight < v.weight();
  }

};

typedef std::deque<VertexImpl> ListVertex;

class GraphImpl {
  ListVertex _vertices;

public:

  GraphImpl() {}

  void addVertex(const VertexImpl &v) {
    _vertices.push_back(v);
  }

  ListVertex vertices() {
    return _vertices;
  }

  const unsigned int size() const {
    return _vertices.size();
  }

};

const Weight penality(const unsigned int size) {
  return size * size;
}

/**
 * This main is temporary and only usable to probe for compilation errors as the third-party makefile only compiles the files which are dependencies of the main file.
 */
int main() {
  typedef PenalizedGraphAlgorithm<GraphImpl, VertexImpl, Weight> PGraphAlgorithm;

  PGraphAlgorithm algorithm(0,&penality);

  GraphImpl graphA, graphB;

  graphA.addVertex(VertexImpl(5));
  graphA.addVertex(VertexImpl(5));

  graphB.addVertex(VertexImpl(10));
  graphB.addVertex(VertexImpl(5));
  graphB.addVertex(VertexImpl(5));

  std::cout << "Total graph A weight: " << algorithm.totalWeightGraph(graphA) << "." << std::endl;
  std::cout << "Total graph B weight: " << algorithm.totalWeightGraph(graphB) << "." << std::endl;
  std::cout << "Total graph AuB weight: " << algorithm.totalWeightUnion(graphA, graphB) << "." << std::endl;

  return 0;
}