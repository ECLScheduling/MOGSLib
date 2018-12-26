#pragma once

#include <abstractions/context/base.h>
#include <mogslib/constants.h>

namespace MOGSLib { namespace Context {

struct OpenMPBase {
  using Id = typename Base<>::Id;

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