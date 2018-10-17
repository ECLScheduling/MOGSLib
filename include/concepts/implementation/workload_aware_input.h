#pragma once

#include <vector>

BEGIN_NAMESPACE(Concept)

/**
 * @brief A concrete concept that fulfills the access to task and PE workload inputs.
 */
class WorkloadAwareInput : public Abstraction::Concept {
public:
  using Index = MOGSLib::Index;
  using Load = MOGSLib::Load;

  std::vector<Index> task_ids;
  std::vector<Index> PE_ids;

  std::vector<Load> tasks;
  std::vector<Load> PEs;

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   */
  inline Index ntasks() {
    return tasks.size();
  }

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index ntasks() const {
    return tasks.size();
  }

  /**
   * @brief Gets the workload of every task in the input.
   */
  inline Load* tasks_workloads() {
    return tasks.data();
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index nPEs() const {
    return PEs.size();
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   */
  inline Index nPEs() {
    return PEs.size();
  }

  /**
   * @brief Gets the workload of every PE in the input.
   */
  inline Load* PEs_workloads() {
    return PEs.data();
  }
};

END_NAMESPACE