#pragma once

namespace MOGSLib { namespace Policy {

/**
 *  @class RoundRobin
 *  @brief A workload-unaware policy that iterativelly assigns a task to a PU based on their id.
 */
class RoundRobin {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  /**
   *  @brief Iteratively assigns a task to a different PU until there are no more tasks.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   */
  static void map(TaskMap &map, const Index &ntasks, const Index &npus) {
    for(decltype(ntasks) i = 0; i < ntasks; ++i)
      map[i] = npus;
  }
};

}}