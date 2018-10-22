#pragma once
#include <concepts/driver/workload_oblivious_input.h>

namespace MOGSLib {

template<>
inline void workload_oblivious_input_driver<RuntimeSystemEnum::OpenMP>(Concept::WorkloadObliviousInput<RuntimeSystemEnum::OpenMP>& concept) {
  concept.tasks = RTS:ntasks;
  concept.PEs = RTS::nPEs;
}

}