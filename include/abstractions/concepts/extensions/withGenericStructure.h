#pragma once

/**
 * @brief A virtual class extension to add a meta-structure to the child class.
 * @details This extensions is meant to be used with alongside strategies that requires small additional structures as input.
 */
template<typename T>
class WithGenericStructure {
public:

  /**
   * @brief A method to obtain the additional input structure.
   */
  virtual T& structure() = 0;

};