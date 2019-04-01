#pragma once

#include <structures/input/base.h>

namespace MOGSLib { namespace Context {

template<typename _Id>
struct Base {
  using Id = _Id;

  MOGSLib::Input::Base<Id> _input;
  Id _k;

  auto& input() {
    return _input;
  }

  auto& k() {
    return _k;
  }

};

}}