#pragma once

namespace MOGSLib { namespace Input {

/**
 *  @class Minimal
 *  @brief The default implementation for the minimal input structure.
 *
 *  This structure uses 2 numeric variables to track both the amount of tasks and pus.
 */
template<typename I>
struct Base {
  using Id = I;
  
  Id tasks, pus;

  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   */
  Id ntasks() { return tasks; }

  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   *  @details This method has a const specifier.
   */
  Id ntasks() const { return tasks; }

  /**
   *  @brief Gets the amount of PEs in a scheduler input.
   */
  Id npus() { return pus; }

  /**
   *  @brief Gets the amount of PEs in a scheduler input.
   *  @details This method has a const specifier.
   */
  Id npus() const { return pus; }
};

}}