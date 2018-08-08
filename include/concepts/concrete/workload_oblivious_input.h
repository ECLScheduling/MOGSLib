#pragma once

#include <vector>

#include <system/type_definitions.h>
#include <system/static.h>

BEGIN_NAMESPACE(Adapter)

/**
 * @brief A concrete concept that fulfills both PEData and TaskData concepts but does not contemplate the workload parts of them.
 * @details This Adapter is the most efficient implementation of the concepts but can only be used in strategies that are not workload aware.
 */
struct WorkloadObliviousInput {
  using Index = MOGSLib::Index;
  
  Index tasks, PEs;

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   */
  inline Index ntasks() {
    return tasks;
  }

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index ntasks() const {
    return tasks;
  }

  /**
   * @brief Gets the workload of every task in the input.
   */
  inline Load* tasks_workloads() {
    return nullptr;
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index nPEs() const {
    return PEs;
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   */
  inline Index nPEs() {
    return PEs;
  }

  /**
   * @brief Gets the workload of every PE in the input.
   */
  inline Load* PEs_workloads() {
    return nullptr;
  }
};

END_NAMESPACE