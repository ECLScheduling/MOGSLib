#pragma once

#include <concepts/implementation/workload_oblivious_input.h>

namespace MOGSLib { namespace Concept {

/**
 * @brief A concrete concept that fulfills the access to task and PE workload inputs.
 */
class WorkloadAwareInput : public WorkloadObliviousInput<> {
public:
  using Index = WorkloadObliviousInput::Index;
  using Load = MOGSLib::Load;

  std::vector<Load> tasks, PEs;

  /**
   * @brief Gets the workload of every task in the input.
   */
  inline Load* tasks_workloads() {
    return tasks.data();
  }

  /**
   * @brief Gets the workload of every PE in the input.
   */
  inline Load* PEs_workloads() {
    return PEs.data();
  }
};

}}