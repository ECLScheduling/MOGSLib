#pragma once

#include "greedyStrategy.h"

// ###########################################
// GreedyStrategyInitialLoad concept definition.
// ###########################################

/**
 * This static structure defines the input's concept for the GreedyStrategyInitialLoad at compile time. If the passed type does not conform to the input type, there will be errors issued at compile time.
 */
template<typename InputType>
struct GreedyStrategyInitialLoadConcept {
  static const bool Conforms = GreedyStrategyConcept<InputType>::Conforms && std::is_base_of<WithStartingLoad, InputType>::value;
};

// ###########################################
// GreedyStrategyInitialLoad class definition.
// ###########################################

/**
 * Template class used to generate a static type-error when the GreedyStrategy tries to be used with a class that is not child of it's input requires.
 */
template<typename InputType, bool = GreedyStrategyInitialLoadConcept<InputType>::Conforms >
class GreedyInitialLoadStrategy : public GreedyStrategy<InputType, false> {
  static_assert(GreedyStrategyInitialLoadConcept<InputType>::Conforms, "The GreedyStrategyInitialLoad 'InputType' must inherit from the baseclass 'BasicInput' and implement the extension 'WithStartingLoad'.");
};

template<typename InputType>
class GreedyInitialLoadStrategy<InputType, true> : public GreedyStrategy<InputType, true> {
  typedef GreedyStrategy<InputType, true> BaseStrategy;
  typedef typename BaseStrategy::MinHeap MinHeap;
  typedef typename BaseStrategy::LoadBearer LoadBearer;

  /**
   * This function populates the PEs heap with the ids of the processors and their load is set according to the input object's getPELoad method.
   * @param input The input reference which was passed to the GreedyStrategy.
   */
  virtual void createPEHeap(const InputType &input);

};

#include "greedyStrategyInitialLoad.ipp"