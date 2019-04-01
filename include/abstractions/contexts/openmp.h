#pragma once

#include <structures/input/workload_aware.h>

#include <abstractions/rts/openmp/openmp.h>
#include <omp.h>

namespace MOGSLib { namespace Context {

template<typename I, typename L>
struct OpenMP {
  using Id = I;
  using Load = L;

  MOGSLib::Input::WorkloadAware<Id, Load> _input;

  inline void set_loads(std::vector<Load> &loads) {
    omp_set_ntasks(loads.size());
    _input.tasks = loads;
  }

  inline auto& input() {
    _input.pus.resize(MOGSLib::RTS::OpenMP::threads);
    for(Id i = 0; i < _input.pus.size(); ++i)
      _input.pus[i] = 0;
    return _input;
  }

  inline auto k() { return MOGSLib::RTS::OpenMP::chunks;  }
};

}}