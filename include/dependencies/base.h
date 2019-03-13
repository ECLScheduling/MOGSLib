#pragma once

#include <mogslib/config.h>

namespace MOGSLib { namespace Dependency {

/**
 *  @class Base
 *  @brief The minimal dependencies of a policy.
 */
template<typename I>
struct Base {
  using Id = I;
  using Schedule = typename MOGSLib::Config::Policy<Id>::Schedule;
};

}}