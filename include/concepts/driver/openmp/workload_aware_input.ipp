#pragma once
#include <concepts/driver/workload_aware_input.h>

#include "workload_oblivious_input.ipp"

namespace MOGSLib {

template<>
inline void workload_aware_input_driver<RuntimeSystemEnum::OpenMP>(Concept::WorkloadAwareInput<>& concept) {
  Driver<Concept::WorkloadObliviousInput<RuntimeSystemEnum::OpenMP>, RuntimeSystemEnum::OpenMP>::init(concept);

  concept.task_loads = RTS::get_task_loads();
  concept.pe_loads = RTS::get_PE_loads();
}

}