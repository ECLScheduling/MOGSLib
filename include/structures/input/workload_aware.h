#pragma once

#include <vector>

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
struct WorkloadAware {
  using Id = I;
  using Load = L;
  
  using Loads = std::vector<Load>;

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
  inline Id ntasks() { return tasks.size(); }

  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   *  @details This method has a const specifier.
   */
  inline Id ntasks() const { return tasks.size(); }

  /**
   *  @brief Gets the amount of PEs in a scheduler input.
   */
  inline Id npus() { return pus.size(); }

  /**
   *  @brief Gets the amount of PEs in a scheduler input.
   *  @details This method has a const specifier.
   */
  inline Id npus() const { return pus.size(); }
};

}}