#pragma once

#include <structures/input/workload_aware.h>

namespace MOGSLib { namespace Context {

template<typename _Id, typename _Load>
struct WorkloadAware {
  using Id = _Id;
  using Load = _Load;

  MOGSLib::Input::WorkloadAware<Id, Load> _input;
  Id _k;

  auto& input() {
    return _input;
  }

  auto& k() {
    return _k;
  }

};

}}