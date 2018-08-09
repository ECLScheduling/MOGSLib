#pragma once

#include <system/type_definitions.h>

#include <cstring>

BEGIN_NAMESPACE(Policy)

/**
 * @brief A workload-unaware policy that iterativelly assigns a task to a PE based on their id.
 * @details This policy groups tasks that are adjacent in ordering. This characteristic might result in better cache locality in systems like OpenMP.
 */
class Compact {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  static void map(TaskMap &map, const Index &ntasks, const Index &nPEs) {
    auto size = ntasks/nPEs;
    Index j = 0;
    for(Index i = 0; i < ntasks; i += size){
      for(Index s = 0; s < size; ++s)
        map[i+s] = j;
      ++j;
    }
  }
};

END_NAMESPACE