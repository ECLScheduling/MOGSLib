#pragma once

#include <cstdint>
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
 * @brief The default traits to the system.
 */
template<>
struct Traits<DefaultTypes> : Traits<void> {

  /**
   * @brief The type definition that will serve as an unsigned int inside the library.
   */
  using UInt = uint_fast32_t;

  /**
   * @brief The type definition that will serve to quantify a task's load value for the framework.
   */
  using Load = UInt;
};

template<>
struct Traits<LibDebugger> : Traits<void> {
  constexpr static bool enabled = debugged;

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