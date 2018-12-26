#pragma once

#include <dependencies/base.h>

namespace MOGSLib { namespace Dependency {

/**
 *  @class WorkloadAware
 *  @brief The minimal dependencies of a workload aware policy.
 */
template<typename Idx, typename L>
struct WorkloadAware : public Base<Idx> {
  using Id = typename Base<Idx>::Id;
  using Schedule = typename Base<Idx>::Schedule;

  using Load = L;
};

}}