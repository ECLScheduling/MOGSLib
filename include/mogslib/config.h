#pragma once

#include <vector>
#include <structures/output/alloc.h>

namespace MOGSLib { namespace Config {

template<typename Id>
struct Policy {
  using Schedule = Id*;
};

}}