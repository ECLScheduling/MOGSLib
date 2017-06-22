#pragma once

#include <strategies/abstractStrategy.h>
#include <strategies/input/basicInput.h>
#include <queue>


// ###################################################
// Definitions for the concepts of the GreedyStrategy.
// ###################################################

/**
 * This static structure defines the input's concept for the GreedyStrategy at compile time. If the passed type does not conform to the input type, there will be errors issued at compile time.
 */
template<typename InputType>
struct GreedyStrategyConcept {
  static const bool Conforms = std::is_base_of<BasicInput, InputType>::value;
};

// ################################
// GreedyStrategy class definition.
// ################################

/**
 * Template class used to generate a static type-error when the GreedyStrategy tries to be used with a class that is not child of it's input requires.
 */
template<typename InputType, bool = GreedyStrategyConcept<InputType>::Conforms >
class GreedyStrategy : public AbstractStrategy<InputType> {
  static_assert(GreedyStrategyConcept<InputType>::Conforms, "The GreedyStrategy 'InputType' must inherit from the baseclass 'BasicInput'.");
};

/**
 * Class that implements a greedy trategy to load balancing using the most basic form of input.
 */
template<typename InputType>
class GreedyStrategy<InputType, true> : public AbstractStrategy<InputType> {
public:
  typedef BasicInput::Id Id;
  typedef BasicInput::Load Load;

  /**
   * Internal Helper instruction to decribe both PEs and Tasks by their ids and current load.
   * @variable id The id of the task or PE.
   * @variable load The load of the task or PE.
   */
  struct LoadBearer {
    Id id;
    Load load;

    LoadBearer(const Id &anId, const Load &aLoad) : id(anId), load(aLoad) {}
  };

  /**
   * Internal Helper struct to be used as the max-heap comparator.
   */
  struct MaxHeapComparator {
    inline bool operator ()(const LoadBearer &a, const LoadBearer &b) const {
      return a.load < b.load;
    }
  };

  /**
   * Internal Helper struct to be used as the min-heap comparator.
   */
  struct MinHeapComparator {
    inline bool operator ()(const LoadBearer &a, const LoadBearer &b) const {
      return a.load > b.load;
    }
  };

  typedef std::priority_queue<LoadBearer, std::vector<LoadBearer>, MaxHeapComparator > MaxHeap;
  typedef std::priority_queue<LoadBearer, std::vector<LoadBearer>, MinHeapComparator > MinHeap;

  /**
   * @variable PEs The min-heap of PEs used in the greedy strategy.
   */
  MinHeap PEs;

  /**
   * @variable Tasks The max-heap of Tasks used in the greedy strategy.
   */
  MaxHeap tasks;

  virtual ~GreedyStrategy() {}

  /**
   * This function populates the PEs heap with the ids of the processors and their load is set to 0.
   * @param input The input reference which was passed to the GreedyStrategy.
   */
  virtual void createPEHeap(const InputType &input);

  /**
   * This function populates the Tasks heap with the ids and loads of the input's tasks.
   * @param input The input reference which was pased to the GreedyStrategy.
   */
  virtual void createTaskHeap(const InputType &input);

  /**
   * The bootstrap function which will start the strategy's implementation.
   */
  virtual void doTaskMapping(const InputType &input);

};

#include "greedyStrategy.ipp"