#pragma once

#include <system/traits.h>

namespace MOGSLib { namespace Policy {

/**
 *  @class RoundRobin
 *  @tparam Id An index type to organize PUs and tasks.
 *  @brief A workload-unaware policy that iterativelly assigns a task to a PU based on their id.
 */
template<typename Id>
class RoundRobin {
public:
  using Index = Id;
  using Schedule = typename MOGSLib::Traits::Policy<Id>::Output;

  /**
   *  @brief Iteratively assigns a task to a different PU until there are no more tasks.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   */
  static void map(Schedule &map, const Index &ntasks, const Index &npus) {
    for(Index i = 0; i < ntasks; ++i)
      map[i] = i%npus;
  }
};

}}