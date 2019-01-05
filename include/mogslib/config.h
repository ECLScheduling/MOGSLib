#pragma once

#include <vector>
#include <structures/output/cycle.h>

namespace MOGSLib { namespace Config {

template<typename Id>
struct Policy {
  using Schedule = Id*;
};

}}