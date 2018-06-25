#pragma once

#include <cstdint>
#include <cstddef>
#include "system/types.h"

/**
 * @brief General Traits used by most library components.
 */
template<typename T>
struct Traits {};

/**
 * @brief The default types in the framework.
 */
template<>
struct Traits<DefaultTypes> {

  /**
   * @brief The type definition that will serve as index inside the framework.
   */
  using Index = std::size_t;

  /**
   * @brief The type definition that will serve to quantify a load values for the framework.
   */
  using Load = uint_fast32_t;
};

template<>
struct Traits<Policies> : Traits<DefaultTypes> {
  using TaskEntry = Index;
  using TaskMap = TaskEntry*;
};