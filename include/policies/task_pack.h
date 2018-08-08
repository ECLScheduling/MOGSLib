#pragma once

#include <system/type_definitions.h>

BEGIN_NAMESPACE(Policy)

/**
 * @brief A workload-unaware policy that iterativelly assigns a task to a PE based on their id.
 * @details This policy aggregates adjacent tasks into task packs that are assigned to the same PE.
 */
class TaskPack {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  static void map(TaskMap &map, const Index &ntasks, const Index &nPEs, const Index &npacks) {
    auto pack_size = ntasks/npacks;
    auto left_over = ntasks%npacks;

    for(Index i = 0; i < left_over; ++i)
      map[i] = 0;

    for(Index i = left_over; i < npacks; ++i)
      for(Index j = i; j < ntasks; ++j)
        map[i*pack_size + left_over] = i;
  }
};

END_NAMESPACE