#include <concepts/implementation/workload_aware_input.h>
#include <rts/openmp.h>

BEGIN_NAMESPACE(Concept)

template<MOGSLib::Abstraction::RuntimeSystemEnum T>
void temp_omp_func_aware(WorkloadAwareInput& concept) {}

template<>
void temp_omp_func_aware<MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP>(WorkloadAwareInput& concept) {
  concept.tasks.resize(MOGSLib::RTS::OpenMP::ntasks);
  concept.PEs.resize(MOGSLib::RTS::OpenMP::nPEs);
}

template<>
struct Driver<WorkloadAwareInput, MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP> {
  using Initializer = void (*)(WorkloadAwareInput&);

  static constexpr Initializer initializer = temp_omp_func_aware<MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP>;
};

END_NAMESPACE