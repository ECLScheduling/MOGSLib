#pragma once

#include "declaration.h"

namespace MOGSLib { namespace Scheduler {

/**
 * @brief An implementation of the methods required by the simple input structure.
 * @details This structure uses 2 numeric variables to track both the amount of tasks and pus.
 */
struct SimpleInput : public Input<MOGSLib::InputType::simple> {
  Index task_count, pu_count;

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   */
  Index ntasks() { return task_count; }

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  Index ntasks() const { return task_count; }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   */
  Index npus() { return pu_count; }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   * @details This method has a const specifier.
   */
  Index npus() const { return pu_count; }
};

}}