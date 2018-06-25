#pragma once

#include <system/type_definitions.h>

namespace Policy {

class RoundRobin {
public:

  static void map(TaskMap &map, const Index &ntasks, const Index &nPEs) {
    for(Index i = 0; i < ntasks; ++i)
      map[i] = i%nPEs;
  }

};

}