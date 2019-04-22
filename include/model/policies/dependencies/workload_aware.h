#pragma once

#include "base.h"

namespace MOGSLib { namespace Dependency {

/**
 *  @class WorkloadAware
 *  @brief The minimal dependencies of a workload aware policy.\
 *  @details It defines the Load type in addition to the Base dependencies definitions.
 */
template<typename Idx, typename L>
struct WorkloadAware : public Base<Idx> {
  using Id = typename Base<Idx>::Id;
  using Schedule = typename Base<Idx>::Schedule;

  using Load = L;
};

}}