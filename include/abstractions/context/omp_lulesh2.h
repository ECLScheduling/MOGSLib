#pragma once

#include <abstractions/context/omp_base.h>
#include <lulesh.h>

namespace MOGSLib { namespace Context {

struct Lulesh2 : public OpenMPBase {
  using Id = typename OpenMPBase::Id;
  using Load = typename OpenMPBase::Load;

  Domain *domain;

  void writeback_loop() {
    auto n = domain->numNode();
    auto& loads = _input.tasks;

    set_iterations(n);
    for(auto i = 0; i < n; ++i)
      loads[i] = domain->nodeElemCount(i);
  }
};

}}