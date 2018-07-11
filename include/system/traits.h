#pragma once

#include <cstdint>
#include <cstddef>
#include <string>

#include "system/types.h"

namespace MOGSLib {

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
  //using Index = std::size_t;
  using Index = unsigned int;

  /**
   * @brief The type definition that will serve to quantify a load values for the framework.
   */
  //using Load = uint_fast32_t;
  using Load = unsigned int;
};

template<>
struct Traits<Policies> : Traits<DefaultTypes> {
  using TaskEntry = Index;
  using TaskMap = TaskEntry*;
};

template<SchedulerTypes T>
struct SchedulerTraits : Traits<void> {};

template<>
struct SchedulerTraits<SchedulerTypes::RoundRobin> {
  static constexpr auto name = "roundrobin";
};

template<>
struct SchedulerTraits<SchedulerTypes::Greedy> {
  static constexpr auto name = "greedy";
};

template<>
struct SchedulerTraits<SchedulerTypes::Null> {
  static constexpr auto name = "null";
};

}