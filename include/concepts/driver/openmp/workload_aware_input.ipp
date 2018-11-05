#pragma once
#include <concepts/driver/workload_aware_input.h>

#include "workload_oblivious_input.ipp"

namespace MOGSLib {

template<>
inline void workload_aware_input_driver<RuntimeSystemEnum::OpenMP>(Concept::WorkloadAwareInput& concept) {
  Driver<Concept::WorkloadObliviousInput<RuntimeSystemEnum::OpenMP>, RuntimeSystemEnum::OpenMP>::init(concept);

  // If the RTS has functions associated to inform load, use them. If not, fallback workloads are considered to be 0.
  concept.alloc_tasks = (RTS::get_task_loads == nullptr);
  concept.alloc_PEs = (RTS::get_PE_loads == nullptr);
  concept.clear_memory();
  
  concept.task_loads = (concept.alloc_tasks)? new Load[concept.ntasks()]() : RTS::get_task_loads();
  concept.PE_loads = (concept.alloc_PEs)? new Load[concept.nPEs()]() : RTS::get_PE_loads();
}

}