#pragma once

#include <concepts/implementation/workload_oblivious_input.h>

namespace MOGSLib { namespace Concept {

/**
 * @brief A concrete concept that fulfills the access to task and PE workload inputs.
 */
class WorkloadAwareInput : public WorkloadObliviousInput<> {
public:
  using Load = MOGSLib::Load;

  Load* task_loads, *PE_loads;
  bool alloc_tasks, alloc_PEs;

  WorkloadAwareInput() {
    task_loads = nullptr;
    PE_loads = nullptr;
    
    alloc_tasks = false;
    alloc_PEs = false;
  }

  /**
   * @brief clear the memory if the allocation was made within the scope of the class.
   */
  void clear_memory() {
    if(alloc_tasks && PE_loads != nullptr) {
      delete [] PE_loads;
      PE_loads = nullptr;
      alloc_tasks = false;
    }
    if(alloc_PEs && task_loads != nullptr) {
      delete [] task_loads;
      task_loads = nullptr;
      alloc_PEs = false;
    }
  }

  /**
   * @brief Check if allocated memory can be reused to hold a new amount of task and PE data.
   */
  bool can_reuse_memory(const Index &new_PE_count, const Index &new_task_count) const {
    return (PE_loads != nullptr && nPEs() >= new_PE_count) && (task_loads != nullptr && ntasks() >= new_task_count);
  }

  virtual ~WorkloadAwareInput() {
    clear_memory();
  }

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
    return PE_loads;
  }
};

}}