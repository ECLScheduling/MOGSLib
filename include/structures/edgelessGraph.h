#pragma once

#include <system/traits.h>
#include <vector>

/**
 * Simpĺe implementation of a vertex that has no edges attached to it.
 */
class EdgelessVertex {
public:

  typedef Traits<EdgelessVertex>::Weight Weight;
  typedef Traits<EdgelessVertex>::Id Id;

  /**
   * The identifier of the vertex.
   */
  Id id;

protected:

  /**
   * The weight of the vertex.
   */
  Weight _weight;

public:

  /**
   * Constructor used for allocating vectors.
   * @details This constructor should not be used for other purposes as it doesn't initializes weight or id correctly.
   */
  EdgelessVertex() {}

  /**
   * A constructor to initialize the weight.
   * @param weight A weight value to the vertex.
   */
  EdgelessVertex(const Id &anId, const Weight &weight) : id(anId), _weight(weight) {}

  /**
   * @return The weight of the vertex.
   */
  inline const Weight weight() const {
    return _weight;
  }

  /**
   * A comparator that evaluates two vertices by their weight.
   */
  const bool operator <(const EdgelessVertex &v) const {
    return _weight < v.weight();
  }

};

/**
 * A simple implementation of an graph without edges, which is a graph compound by a set of EdgelessVertex.
 * @param VertexTraits A trait that will point the Graph to where it can resolve it's type definitions.
 */
template<typename VertexTraits = EdgelessGraphDefaultTraits>
class EdgelessGraph {

public:

  typedef typename VertexTraits::Vertex Vertex;
  typedef typename VertexTraits::Weight Weight;
  typedef typename VertexTraits::Id Id;
  typedef typename std::vector<Vertex> VerticesArray;

protected:

  /**
   * The array of vertices in the graph.
   */
  VerticesArray _vertices;

  /**
   * The last weight value set to the graph. The value will be wrong after a vertex is added or removed unless overwritten.
   */
  Weight weightBuffer;

public:

  /**
   * The identifier of the Graph.
   */
  Id id;

  /**
   * Constructor used for allocating vectors.
   * @details This constructor should not be used for other purposes as it doesn't initializes weight and id correctly.
   */
  EdgelessGraph() {
    weightBuffer = VertexTraits::zeroRef;
  }

  /**
   * Constructor that initializes the id and the current weight buffer to zero a zero reference in the traits<Vertex>.
   * @param anId The identifier of the graph.
   */
  EdgelessGraph(const Id &anId) : id(anId) {
    weightBuffer = VertexTraits::zeroRef;
  }

  /**
   * @return The last saved weight value for the graph.
   */
  inline const Weight weight() const {
    return weightBuffer;
  }

  /**
   * @param weight A new calculated weight for the graph.
   */
  inline void setWeight(const Weight &weight) {
    weightBuffer = weight;
  }

  /**
   * Adds a vertex to the graph but does not update it's weight.
   * @param vertex The new graph's vertex.
   */
  inline void addVertex(const EdgelessVertex &vertex) {
    _vertices.push_back(vertex);
  }

  /**
   * @return Get the standard C array that contains the vertices.
   */
  inline Vertex * vertices() {
    return &_vertices[0];
  }

  /**
   * @return The ammount of vertices in the graph.
   */
  inline const unsigned int verticesSize() const {
    return _vertices.size();
  }

  /**
   * A comparator that evaluate two graphs by their weight.
   */
  const bool operator >(const EdgelessGraph<VertexTraits> &g) const {
    return weightBuffer > g.weight();
  }

};