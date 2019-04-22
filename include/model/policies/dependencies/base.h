#pragma once

#include <vector>

namespace MOGSLib { namespace Dependency {

/**
 *  @class Base
 *  @brief The minimal dependencies of a policy.
 *  @details It defines the index type of processing units and work units. Additionally, it defines the Schedule type.
 */
template<typename I>
struct Base {
  using Id = I;
  using Schedule = std::vector<Id>;
};

}}