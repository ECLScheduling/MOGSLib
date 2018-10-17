#pragma once

#include <vector>

BEGIN_NAMESPACE(Concept)

/**
 * @brief A concrete concept that access information about the amount of PEs and work units in the system.
 */
class WorkloadObliviousInput : public Abstraction::Concept {
public:
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