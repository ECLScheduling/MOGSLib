#pragma once
#include <concepts/driver/workload_aware_input.h>

namespace MOGSLib {

template<>
inline void workload_aware_input_driver<RuntimeSystemEnum::OpenMP>(Concept::WorkloadAwareInput& concept) {
  concept.tasks.resize(RTS::ntasks);
  concept.PEs.resize(RTS::nPEs);
}

}