#pragma once

#include <structures/input/workload_aware.h>

namespace MOGSLib { namespace Context {

template<typename I, typename L>
struct WorkloadAware {
  using Id = I;
  using Load = L;
  
  static MOGSLib::Input::WorkloadAware<Id, L> _input;
  static Id _k;

  inline static auto input() {
    return _input;
  }

  inline static auto k() {
    return _k;
  }
};

}}