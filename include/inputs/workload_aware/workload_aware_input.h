#pragma once

#include "declaration.h"

namespace MOGSLib { namespace Scheduler {

/**
 * @brief The implementation of the workload aware concept.
 * @details This implementation uses vector to keep the load values for pus and tasks.
 */
struct WorkloadAwareInput : public Input<MOGSLib::InputType::workload_aware> {
  std::vector<Load> task_loads, pu_loads;

  /**
   * @brief Gets the workload of every task in the input.
   */
  inline Load* task_workloads() {  return task_loads.data(); }

  /**
   * @brief Gets the workload of every PE in the input.
   */
  inline Load* pu_workloads() {  return pu_loads.data(); }

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   */
  inline Index ntasks() { return task_loads.size(); }

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index ntasks() const { return task_loads.size(); }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   */
  inline Index npus() { return pu_loads.size(); }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index npus() const { return pu_loads.size(); }
};

}}