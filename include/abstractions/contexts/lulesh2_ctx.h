#pragma once

#include <structures/input/workload_aware.h>

#include <abstractions/rts/openmp/openmp.h>
#include <omp.h>

#include <lulesh.h>

namespace MOGSLib { namespace Context {

struct Lulesh2 {
  using Id = typename Traits::Id;
  using Load = typename Traits::Load;

  static MOGSLib::Input::WorkloadAware<Id, Load> _input;

  static inline void set_iterations(const Id &n) {
    _input.tasks.resize(n);
    omp_set_taskmap_size(n);
  }

  static inline auto& input() {
    _input.pus.resize(MOGSLib::RTS::OpenMP::threads);
    for(Id i = 0; i < _input.pus.size(); ++i)
      _input.pus[i] = 0;
    return _input;
  }

  static inline auto k() { return MOGSLib::RTS::OpenMP::chunks;  }

  static inline void set_domain(Domain *domain) {
    auto n = domain->numNode();
    auto& loads = _input.tasks;

    set_iterations(n);
    for(auto i = 0; i < n; ++i)
      loads[i] = domain->nodeElemCount(i);
  }
};

decltype(Lulesh2::_input) Lulesh2::_input;

}}