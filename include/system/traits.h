#pragma once

#include <cstdint>
#include <cstddef>
#include <system/types.h>

/**
 * @brief General Traits used by most library components.
 */
template<typename T>
struct Traits {
  /**
   * @brief A flag to indicate if a component is active.
   */
  constexpr static bool enabled = true;

  /**
   * @brief A flag to indicate if debugging is enabled for a given component.
   */
  constexpr static bool debugged = true;

  /**
   * @brief A flag to indicate if a detailed debugging is enabled for a given component.
   */
  constexpr static bool histerically_debugged = false;
};

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

/**
 * @brief The traits corresponding to the scheduler input types.
 */
template<>
struct Traits<SchedulerInput> : Traits<DefaultTypes> {
};

/**
 * @brief The traits corresponding to the scheduler output types.
 */
template<>
struct Traits<SchedulerOutput> : Traits<SchedulerInput> {

  /**
   * @brief The type definition representing the scheduler concrete output.
   */
  using Output = Index*;
};

template<>
struct Traits<LibDebugger> : Traits<void> {
  constexpr static bool enabled = true;

  /**
   * @brief A flag to indicate whether the debugger should print error messages.
   */
  constexpr static bool error = true;

  /**
   * @brief A flag to indicate whether the debugger should print warning messages.
   */
  constexpr static bool warning = true;

  /**
   * @brief A flag to indicate whether the debugger should print information messages.
   */
  constexpr static bool info = false;

  /**
   * @brief A flag to indicate whether the debugger should print trace messages.
   */
  constexpr static bool trace = true;
};

/**
 * @brief Traits for the unit tests in the composition of library elements.
 */
template<>
struct Traits<LibTests> : Traits<void> {
  constexpr static bool debugged = true;
};

/**
 * @brief Traits for the algorithm components of the library.
 */
template<>
struct Traits<LibAlgorithms> : Traits<void> {
  constexpr static bool debugged = histerically_debugged;
};

/**
 * @brief Traits for the strategies components of library.
 */
template<>
struct Traits<LibStrategies> : Traits<void> {
  constexpr static bool debugged = true;
};

/**
 * @brief Traits for the adaptors components of library.
 */
template<>
struct Traits<LibAdaptors> : Traits<void> {
  constexpr static bool debugged = histerically_debugged;
};

template<typename T>
struct Defaults {};

template<>
struct Traits<Policy> : Traits<DefaultTypes> {
  using TaskEntry = Index;
  using TaskMap = TaskEntry*;
};