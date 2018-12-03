#pragma once

#include <system/type_definitions.h>
#include <abstractions/input.h>

namespace MOGSLib { namespace Scheduler {

/**
 * \brief The concept to be implemented by workload aware input for schedulers.
 */
template<>
struct Input<MOGSLib::InputType::WorkloadAware> : public Input<MOGSLib::InputType::Simple> {
  using Load = MOGSLib::Load;

  /**
   * \brief Gets the workload of every task in the input.
   */
  virtual Load* task_workloads() = 0;

  /**
   * \brief Gets the workload of every PE in the input.
   */
  virtual Load* pu_workloads() = 0;
};

}}