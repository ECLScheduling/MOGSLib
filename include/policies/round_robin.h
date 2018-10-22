#pragma once

BEGIN_NAMESPACE(Policy)

/**
 * @brief A workload-unaware policy that iterativelly assigns a task to a PE based on their id.
 */
class RoundRobin {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  static void map(TaskMap &map, const Index &ntasks, const Index &nPEs) {
    for(Index i = 0; i < ntasks; ++i)
      map[i] = i%nPEs;
  }
};

END_NAMESPACE