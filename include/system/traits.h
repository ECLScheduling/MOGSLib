#pragma once

#include "types.h"
#include <cstdint>
#include <map>
#include <set>
#include <queue>

//#########################
// Global Traits
//#########################

template<typename T>
struct Traits {
  
  /**
   * The type definition that will serve to identify tasks and PEs of the system inside the framework.
   */
  typedef uint_fast32_t Id;

  /**
   * The type definition that will serve to quantify a task's load value for the framework.
   */
  typedef uint_fast32_t Load;
};

//#########################
// Input Traits
//#########################

template<>
struct Traits<BasicInput> : Traits<void> {

  /**
   * Type definition of the structure used to represent the set of processing elements in the BasicInput.
   */
  typedef std::set<Id> SetOfId;

  /**
   * Type definition of the structure used to represent the task set in the BasicInput.
   */
  typedef std::map<Id, Load> LoadMap;
};

//#########################
// Structure Traits
//#########################

template<>
struct Traits<EdgelessVertex> : Traits<void> {

  /**
   * Type definition of the weight of a vertex and graph for this structure.
   */
  typedef Load Weight;
  const static Weight zeroRef = 0;
};

struct EdgelessGraphTraits : Traits<EdgelessVertex> {

  /**
   * The type of the vertex used by the EdgelessGraph when loaded with this trait.
   */
  typedef EdgelessVertex Vertex;
};


//#########################
// Algorithms default Traits
//#########################

template<typename Task, typename PE>
struct GreedyStrategyAlgorithmTraits : Traits<void> {
  /**
   * Internal Helper struct to be used as the max-heap comparator.
   */
  struct MaxHeapComparator {
    inline bool operator ()(const Task &a, const Task &b) const {
      return a < b;
    }
  };

  /**
   * Internal Helper struct to be used as the min-heap comparator.
   */
  struct MinHeapComparator {
    inline bool operator ()(const PE &a, const PE &b) const {
      return a > b;
    }
  };

  /**
   * Type used as a max heap for the greedy algorithm.
   */
  typedef std::priority_queue<Task, std::vector<Task>, MaxHeapComparator > MaxHeap;
  
  /**
   * Type used as a min heap for the greedy algorithm.
   */
  typedef std::priority_queue<PE, std::vector<PE>, MinHeapComparator > MinHeap;
};

struct PenalizedGraphAlgorithmTraits {

  /**
   * The default Graph type for the PenalizedGraphAlgorithm, which depends on the Vertex type.
   */
  typedef EdgelessGraph<EdgelessGraphTraits> Graph;

};