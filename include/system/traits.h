#pragma once

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
  using UInt = uint_fast32_t;
  
  /**
   * The type definition that will serve to identify tasks and PEs of the system inside the framework.
   */
  using Id = UInt;

  /**
   * The type definition that will serve to quantify a task's load value for the framework.
   */
  using Load = UInt;

};


//#########################
// Algorithms default Traits
//#########################

template<typename Task, typename PE>
struct GreedyStrategyAlgorithmTraits : Traits<void> {
  
  /**
   * Default type used as a max heap for the greedy algorithm.
   */
  using MaxHeap = std::vector<Task>;
  
  /**
   * Default used as a min heap for the greedy algorithm.
   */
  using MinHeap = std::vector<PE>;
};