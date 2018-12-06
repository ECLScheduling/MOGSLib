#pragma once

#include <system/datatypes.h>
#include "round_robin.h"

namespace MOGSLib { namespace Policy {

/**
 *  @class Compact
 *  @tparam PolicyTypes A specialized structure to define the necessary basic types for schedulers.
 *  @brief A workload-unaware policy that divides the tasks into equally sized groups and assign them to PUs.
 *  
 *  This policy groups tasks that are adjacent in ordering.
 *  This characteristic might result in better cache locality in systems like OpenMP.
 */
template<typename PolicyTypes>
class Compact {
public:
  using Index = typename PolicyTypes::Index;
  using Schedule = typename PolicyTypes::Schedule;

  /**
   *  @brief Divide the tasks into groups and assign them to PUs in increasing index.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   */
  static void map(Schedule &map, const Index &ntasks, const Index &npus) {
    if(npus > ntasks) {
      RoundRobin<PolicyTypes>::map(map, ntasks, npus);
      return;
    }
    auto size = ntasks/npus;
    Index j = 0;
    for(Index i = 0; i < ntasks; i += size){
      for(Index s = 0; s < size; ++s)
        map[i+s] = j;
      ++j;
    }
  }
};

}}