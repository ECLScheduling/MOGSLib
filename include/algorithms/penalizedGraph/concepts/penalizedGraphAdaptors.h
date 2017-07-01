#pragma once 

namespace PenalizedGraphConcepts {

/**
 * An abstract class that fulfills the VertexConcept with generic vertex type.
 * @type WeightType The type of the vertex's weight. It can be any type that can be directly compared with mathematical operators.
 */
template<typename WeightType>
class VertexAdaptor {
public:

  typedef WeightType Weight;

  virtual Weight weight() = 0;
};

/**
 * An abstract class that fulfills the GraphConcept with generic vertex type.
 * @param VertexType The type of vertex this graph contains. It can be any type that conforms to the PenalizedGraphAlgorithmConcept about vertices.
 */
template<typename VertexType>
class GraphAdaptor {
public:

  typedef VertexType Vertex;
  typedef typename Vertex::Weight Weight;

  virtual Weight weight() = 0;
  virtual Vertex* vertices() = 0;
  virtual unsigned int verticesSize() = 0;
};

}