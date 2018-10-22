#pragma once
#include <concepts/driver/workload_oblivious_input.h>

namespace MOGSLib {

template<>
inline void workload_oblivious_input_driver<RuntimeSystemEnum::Charm>(Concept::WorkloadObliviousInput& concept) {
  auto input = RTS::stats;

  concept.tasks = input->n_objs;
  concept.PEs = input->nprocs();
}

}