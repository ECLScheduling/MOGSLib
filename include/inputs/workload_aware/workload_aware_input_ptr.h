#pragma once

#include <memory>

#include "declaration.h"
#include <inputs/simple/simple_input.h>

namespace MOGSLib { namespace Scheduler {

/**
 * @brief The implementation of the workload aware concept.
 * @details This implementation extends the SimpleInput structure and uses pointer to reference the loads of tasks and pus.
 */
struct WorkloadAwareInputThroughPointer : public Input<MOGSLib::InputType::workload_aware>, public SimpleInput {
  std::unique_ptr<Load> task_loads, pu_loads;

  /**
   * @brief Gets the workload of every task in the input.
   */
  inline Load* task_workloads() {  return task_loads.get(); }

  /**
   * @brief Gets the workload of every PE in the input.
   */
  inline Load* pu_workloads() {  return pu_loads.get(); }
};

}}