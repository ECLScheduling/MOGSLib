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
   * The type definition that will serve as an unsigned int inside the library.
   */
  typedef uint_fast32_t UInt;
  
  /**
   * The type definition that will serve to identify tasks and PEs of the system inside the framework.
   */
  typedef UInt Id;

  /**
   * The type definition that will serve to quantify a task's load value for the framework.
   */
  typedef UInt Load;

  /**
   * Reference to the zero value of the Load type.
   */
  const static Load zeroRef = 0;

  /**
   * A tag to check wether the struct must be debugged.
   */
  const static bool debug = false;
};

//#########################
// Input Traits
//#########################

struct DefaultInputTraits : Traits<void> {

  /**
   * Type definition of the structure used to represent a Task.
   */
  typedef SimpleTask<Id, Load> Task;

  /**
   * Type definition of the structure used to represent a PE (Processing Element).
   */
  typedef SimplePE<Task> PE;
  
};

//#########################
// Structure Traits
//#########################


//#########################
// Algorithms default Traits
//#########################

template<typename Task, typename PE>
struct GreedyStrategyAlgorithmTraits : Traits<void> {
  /**
   * Internal Helper struct to be used as the max-heap comparator.
   */
  struct MaxHeapComparator {
    inline bool operator ()(const Task *a, const Task *b) const {
      return *a < *b;
    }

    inline bool operator ()(Task *a, Task *b) const {
      return *a < *b;
    }
  };

  /**
   * Internal Helper struct to be used as the min-heap comparator.
   */
  struct MinHeapComparator {
    inline bool operator ()(PE a, PE b) const {
      return a > b;
    }
  };

  /**
   * Type used as a max heap for the greedy algorithm.
   */
  typedef std::priority_queue<Task, std::vector<Task*>, MaxHeapComparator > MaxHeap;
  
  /**
   * Type used as a min heap for the greedy algorithm.
   */
  typedef std::priority_queue<PE, std::vector<PE>, MinHeapComparator > MinHeap;
};


//#########################################
// Strategy Specific Traits
//#########################################


struct EagerMapTraits : Traits<void>{

  /**
   * The data type that represents the communication value of the EagerMap's communication matrix.
   */
  typedef UInt CommValue;

  /**
   * The data type that represents the communication matrix that is used by the EagerMap strategy.
   */
  typedef EagerMap::CommunicationMatrix CommunicationMatrix; 

  typedef EagerMap::TaskGroup TaskGroup;
};