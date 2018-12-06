#pragma once

#include "declaration.h"

namespace MOGSLib { namespace Input {

/**
 *  @class WorkloadAware
 *  @brief The default implementation of the workload aware input structure.
 *  @tparam I the index type.
 *  @tparam L the load type.
 *
 *  This class is defined by two load vectors.
 *  One references the task loads and the other the PUs.
 *  This structure is constructed by copying the values of a vector.
 *  TODO: Define a structure that can reference data rather than copying.
 */
template<typename I, typename L>
struct WorkloadAware : public Declaration<MOGSLib::InputEnum::workload_aware, I, std::vector<L>> {
  using Decl = Declaration<MOGSLib::InputEnum::workload_aware, I, std::vector<L>>;
  using Loads = typename Decl::Loads;
  using Index = typename Decl::Index;

  Loads tasks, pus;

  /**
   *  @brief Gets the workload of every task in the input.
   */
  inline Loads& task_workloads() {  return tasks; }

  /**
   *  @brief Gets the workload of every PE in the input.
   */
  inline Loads& pu_workloads() {  return pus; }

  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   */
  inline Index ntasks() { return tasks.size(); }

  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   *  @details This method has a const specifier.
   */
  inline Index ntasks() const { return tasks.size(); }

  /**
   *  @brief Gets the amount of PEs in a scheduler input.
   */
  inline Index npus() { return pus.size(); }

  /**
   *  @brief Gets the amount of PEs in a scheduler input.
   *  @details This method has a const specifier.
   */
  inline Index npus() const { return pus.size(); }
};

}}