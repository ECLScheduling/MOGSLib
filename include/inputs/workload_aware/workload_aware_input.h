#pragma once

#include "declaration.h"

namespace MOGSLib { namespace Scheduler {

/**
 * \brief The implementation of the workload aware concept.
 * @details This implementation uses a vector to keep the load values for pus and tasks if CopyInput is true.
 */
struct WorkloadAwareInput : public Input<MOGSLib::InputType::workload_aware> {
  using BaseContainer = typename Input<MOGSLib::InputType::workload_aware>::Container;

  /**
   * \brief Gets the workload of every task in the input.
   */
  inline BaseContainer& task_workloads() {  return tasks; }

  /**
   * \brief Gets the workload of every PE in the input.
   */
  inline BaseContainer& pu_workloads() {  return pus; }

  /**
   * \brief Gets the amount of tasks in a scheduler input.
   */
  inline Index ntasks() { return tasks.size(); }

  /**
   * \brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index ntasks() const { return tasks.size(); }

  /**
   * \brief Gets the amount of PEs in a scheduler input.
   */
  inline Index npus() { return pus.size(); }

  /**
   * \brief Gets the amount of PEs in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index npus() const { return pus.size(); }
};

}}