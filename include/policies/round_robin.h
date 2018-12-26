#pragma once

#include <dependencies/base.h>

namespace MOGSLib { namespace Policy {

template<typename ... Deps>
class RoundRobin;

/**
 *  @class RoundRobin
 *  @tparam Id An index type to organize PUs and tasks.
 *  @brief A workload-unaware policy that iterativelly assigns a task to a PU based on their id.
 */
template<typename I>
struct RoundRobin<MOGSLib::Dependency::Base<I>> {
  using Deps = MOGSLib::Dependency::Base<I>;
  using Id = typename Deps::Id;
  using Schedule = typename Deps::Schedule;

  /**
   *  @brief Iteratively assigns a task to a different PU until there are no more tasks.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   */
  static void map(Schedule &map, const Id &ntasks, const Id &npus) {
    for(Id i = 0; i < ntasks; ++i)
      map[i] = i%npus;
  }
};

}}