#pragma once

#include <structures/input/workload_aware.h>

#include <abstractions/rts/openmp/openmp.h>
#include <omp.h>

namespace MOGSLib { namespace Context {

struct OpenMP {
  using Id = typename Traits::Id;
  using Load = typename Traits::Load;

  static MOGSLib::Input::WorkloadAware<Id, Load> _input;

  static inline auto& input() {
    _input.pus.resize(MOGSLib::RTS::OpenMP::threads);
    for(Id i = 0; i < _input.pus.size(); ++i)
      _input.pus[i] = 0;
    return _input;
  }

  static inline auto k() { return MOGSLib::RTS::OpenMP::chunks;  }
};

decltype(OpenMPTest::_input) OpenMPTest::_input;

}}