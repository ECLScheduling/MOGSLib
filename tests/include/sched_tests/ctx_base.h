#pragma once

#include <structures/input/base.h>

namespace MOGSLib { namespace Context {

template<typename _Id>
struct Base {
  using Id = _Id;

  static MOGSLib::Input::Base<Id> _input;
  static Id _k;

  static auto& input() {
    return _input;
  }

    static auto& k() {
    return _k;
  }

};

template<typename I>
MOGSLib::Input::Base<I> Base<I>::_input;

template<typename I>
I Base<I>::_k;

}}