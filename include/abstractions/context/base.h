#pragma once

#include <structures/input/base.h>

namespace MOGSLib { namespace Context {

template<typename I>
struct Base {
  using Id = I;

  static MOGSLib::Input::Base<Id> _input;
  static I _k;

  inline static auto input() {
    return _input;
  }

  inline static auto k() {
    return _k;
  }
};

}}