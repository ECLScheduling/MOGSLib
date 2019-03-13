#pragma once

#include <vector>
#include <structures/output/output.h>

namespace MOGSLib { namespace Config {

template<typename Id>
struct Policy {
  using Schedule = std::vector<Id>;
};

}}