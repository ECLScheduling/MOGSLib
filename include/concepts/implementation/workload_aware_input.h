#pragma once

#include <concepts/implementation/workload_oblivious_input.h>

#include <iostream>

namespace MOGSLib { namespace Concept {

/**
 * @brief A concrete concept that fulfills the access to task and PE workload inputs.
 */
template<MOGSLib::RuntimeSystemEnum R = MOGSLib::TargetSystem>
class WorkloadAwareInput : public WorkloadObliviousInput<> {
public:
  using Load = MOGSLib::Load;

  std::vector<Load> task_loads, pe_loads;

  /**
   * @brief Gets the workload of every task in the input.
   */
  inline Load* tasks_workloads() {
    return task_loads.data();
  }

  /**
   * @brief Gets the workload of every PE in the input.
   */
  inline Load* PEs_workloads() {
    return pe_loads.data();
  }
};

template<>
class WorkloadAwareInput<MOGSLib::RuntimeSystemEnum::OpenMP> : public WorkloadObliviousInput<> {
public:
  using Load = MOGSLib::Load;

  Load *task_loads, *pe_loads;

  /**
   * @brief Gets the workload of every task in the input.
   */
  inline Load* tasks_workloads() {
    return task_loads;
  }

  /**
   * @brief Gets the workload of every PE in the input.
   */
  inline Load* PEs_workloads() {
    return pe_loads;
  }
};

}}