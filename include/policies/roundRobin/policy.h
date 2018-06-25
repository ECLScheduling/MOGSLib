#pragma once

#include <system/traits.h>

namespace Policies {

class RoundRobin {
public:

  using TaskEntry = Traits<Policy>::TaskEntry;
  using TaskMap = Traits<Policy>::TaskMap;
  using Index = Traits<Policy>::Index;

  static void map(TaskMap &map, const Index &ntasks, const Index &nPEs) {
    for(Index i = 1; i < ntasks; ++i)
      map[i] = i%nPEs;
  }

};

}