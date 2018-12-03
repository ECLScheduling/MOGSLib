#pragma once

#include <memory>
#include <inputs/simple/simple_input.h>

namespace MOGSLib { namespace Scheduler {

/**
 * @brief The specialization of the workload aware input witH pointers to values instead of copied vectors.
 * @details This implementation extends the SimpleInput structure and uses pointer to reference the loads of tasks and pus.
 */
template<>
struct WorkloadAwareInput<false> : public Input<MOGSLib::InputType::workload_aware>, public SimpleInput {
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