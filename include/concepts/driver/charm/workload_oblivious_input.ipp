#pragma once

#include <concepts/implementation/workload_oblivious_input.h>
#include <rts/charm.h>

BEGIN_NAMESPACE(Concept)

template<MOGSLib::Abstraction::RuntimeSystemEnum T>
void temp_func(WorkloadObliviousInput& concept) {}

template<>
void temp_func<MOGSLib::Abstraction::RuntimeSystemEnum::Charm>(WorkloadObliviousInput& concept) {
  auto input = MOGSLib::RTS::Charm::stats;

  concept.tasks = input->n_objs;
  concept.PEs = input->nprocs();
}

template<>
struct Driver<WorkloadObliviousInput, MOGSLib::Abstraction::RuntimeSystemEnum::Charm> {
  using Initializer = void (*)(WorkloadObliviousInput&);

  static constexpr Initializer initializer = temp_func<MOGSLib::Abstraction::RuntimeSystemEnum::Charm>;
};

END_NAMESPACE