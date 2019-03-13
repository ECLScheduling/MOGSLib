#pragma once

#include <structures/input/workload_aware.h>

namespace MOGSLib { namespace Context {

template<typename _Id, typename _Load>
struct WorkloadAware {
  using Id = _Id;
  using Load = _Load;

  static MOGSLib::Input::WorkloadAware<Id, Load> _input;
  static Id _k;

  static auto& input() {
    return _input;
  }

  static auto& k() {
    return _k;
  }

};

template<typename I, typename L>
MOGSLib::Input::WorkloadAware<I, L> WorkloadAware<I,L>::_input;

template<typename I, typename L>
I WorkloadAware<I,L>::_k;
}}