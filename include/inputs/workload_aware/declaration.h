#pragma once

#include <inputs/minimal/declaration.h>

namespace MOGSLib { namespace Input {

/**
 *  @class Declaration_WorkloadAware
 *  @brief The declaration of the workload aware input structure for schedulers.
 *  @tparam I The index type.
 *  @tparam L The load type.
 */
template<typename I, typename L>
struct Declaration<MOGSLib::InputEnum::workload_aware, I, L> : public Declaration<MOGSLib::InputEnum::minimal, I> {
  using Index = typename Declaration<MOGSLib::InputEnum::minimal, I>::Index;
  using Loads = L;

  /**
   *  @brief Gets the workload of every task in the input.
   */
  virtual Loads& task_workloads() = 0;

  /**
   *  @brief Gets the workload of every PU in the input.
   */
  virtual Loads& pu_workloads() = 0;
};

}}