#pragma once

#include <vector>

namespace MOGSLib { namespace Config {

template<typename Id>
struct Policy {
  using Schedule = std::vector<Id>;
};

}}