#pragma once

#include <system/type_definitions.h>
#include <system/static.h>

BEGIN_NAMESPACE(Policy)

/**
 * @brief A workload-unaware policy that iterativelly assigns a task to a PE based on their id.
 * @details This policy groups tasks that are adjacent in ordering. This characteristic might result in better cache locality in systems like OpenMP.
 */
class Compact {
public:
  static void map(TaskMap &map, const Index &ntasks, const Index &nPEs) {
    for(Index i = 0; i < ntasks; ++i)
      map[i] = i/nPEs;
  }
};

END_NAMESPACE