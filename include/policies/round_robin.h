#pragma once

#include <system/datatypes.h>

namespace MOGSLib { namespace Policy {

/**
 *  @class RoundRobin
 *  @tparam PolicyTypes A specialized structure to define the necessary basic types for schedulers.
 *  @brief A workload-unaware policy that iterativelly assigns a task to a PU based on their id.
 */
template<typename PolicyTypes>
class RoundRobin {
public:
  using Index = typename PolicyTypes::Index;
  using Schedule = typename PolicyTypes::Schedule;

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