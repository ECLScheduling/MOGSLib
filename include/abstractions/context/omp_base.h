#pragma once

#include <structures/input/workload_aware.h>

#include <abstractions/rts/openmp/openmp.h>
#include <abstractions/rts/openmp/openmp.ipp>

#include <omp.h>

namespace MOGSLib { namespace Context {

struct OpenMPBase {
  using Id = typename SystemTraits<System::libgomp>::Id;
  using Load = typename SystemTraits<System::libgomp>::Load;

  MOGSLib::Input::WorkloadAware<Id, Load> _input;
  Id _k;

  inline void set_iterations(const Id &n) {
    _input.tasks.resize(n);
    omp_set_taskmap_size(n);
  }

  inline auto& input() {
    _input.pus.resize(MOGSLib::RTS::OpenMP::threads);
    return _input;
  }

  inline auto k() {
    _k = MOGSLib::RTS::OpenMP::chunks;
    return _k;
  }
};

}}