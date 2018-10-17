#pragma once

#include <concepts/implementation/workload_oblivious_input.h>
#include <rts/openmp.h>

BEGIN_NAMESPACE(Concept)

template<MOGSLib::Abstraction::RuntimeSystemEnum T>
void temp_omp_func(WorkloadObliviousInput& concept) {}

template<>
void temp_omp_func<MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP>(WorkloadObliviousInput& concept) {
  concept.tasks = MOGSLib::RTS::OpenMP::ntasks;
  concept.adapter->PEs = MOGSLib::RTS::OpenMP::nPEs;
}

template<>
struct Driver<WorkloadObliviousInput, MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP> {
  using Initializer = void (*)(WorkloadObliviousInput&);

  static constexpr Initializer initializer = temp_omp_func<MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP>;
};

END_NAMESPACE