#pragma once

#include <abstractions/contexts/omp_base.h>
#include <lulesh.h>

namespace MOGSLib { namespace Context {

struct Lulesh2 : public OpenMPBase {
  void set_domain(Domain *domain) {
    auto n = domain->numNode();
    auto& loads = _input.tasks;

    set_iterations(n);
    for(auto i = 0; i < n; ++i)
      loads[i] = domain->nodeElemCount(i);
  }
};

}}