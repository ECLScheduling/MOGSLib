#pragma once

#include "declaration.h"

namespace MOGSLib { namespace Input {

/**
 *  @class Minimal
 *  @brief The default implementation for the minimal input structure.
 *
 *  This structure uses 2 numeric variables to track both the amount of tasks and pus.
 */
template<typename I>
struct Minimal : public Declaration<MOGSLib::InputEnum::minimal, I> {
  using Index = typename Declaration<MOGSLib::InputEnum::minimal, I>::Index;
  
  Index n_tasks, n_pus;

  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   */
  Index ntasks() { return n_tasks; }

  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   *  @details This method has a const specifier.
   */
  Index ntasks() const { return n_tasks; }

  /**
   *  @brief Gets the amount of PEs in a scheduler input.
   */
  Index npus() { return n_pus; }

  /**
   *  @brief Gets the amount of PEs in a scheduler input.
   *  @details This method has a const specifier.
   */
  Index npus() const { return n_pus; }
};

}}