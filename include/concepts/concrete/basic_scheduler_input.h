#pragma once

#include <system/type_definitions.h>

namespace Adapter {

/**
 * @brief A concrete concept that fulfills both PEData and TaskData concepts.
 */
struct BasicSchedulerInput {
  Index _ntasks;
  Index _nPEs;

  Load *_task_workloads;
  Load *_PE_workloads;

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   */
  inline Index ntasks() {
    return _ntasks;
  }

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index ntasks() const {
    return _ntasks;
  }

  /**
   * @brief Gets the workload of every task in the input.
   */
  inline Load* tasks_workloads() {
    return _task_workloads;
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index nPEs() const {
    return _nPEs;
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   */
  inline Index nPEs() {
    return _nPEs;
  }

  /**
   * @brief Gets the workload of every PE in the input.
   */
  inline Load* PEs_workloads() {
    return _PE_workloads;
  }
};

}