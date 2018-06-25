#pragma once

#include <system/traits.h>

namespace Policies {

template<@POLICY_DEPS@>
class @POLICY_NAME@ {
public:
  
  using TaskEntry = Traits<Policy>::TaskEntry;
  using TaskMap = Traits<Policy>::TaskMap;p;

  TaskMap operator ()(@POLICY_DEPS_METHOD@) {
  }

};

}