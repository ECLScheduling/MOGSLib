#pragma once

#include <policies/round_robin.h>

namespace MOGSLib { namespace Policy {

template<typename ... Deps>
class Compact;

/**
 *  @class Compact
 *  @tparam Id An index type to organize PUs and tasks.
 *  @brief A workload-unaware policy that divides the tasks into equally sized groups and assign them to PUs.
 *  
 *  This policy groups tasks that are adjacent in ordering.
 *  This characteristic might result in better cache locality in systems like OpenMP.
 */
template<typename I>
struct Compact<MOGSLib::Dependency::Base<I>> {
  using Deps = MOGSLib::Dependency::Base<I>;
  using Id = typename Deps::Id;
  using Schedule = typename Deps::Schedule;

  /**
   *  @brief Divide the tasks into groups and assign them to PUs in increasing index.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   */
  static void map(Schedule &map, const Id &ntasks, const Id &npus) {
    if(npus > ntasks) {
      RoundRobin<Deps>::map(map, ntasks, npus);
      return;
    }
    auto size = ntasks/npus;
    Id j = 0;
    for(Id i = 0; i < ntasks; i += size){
      for(Id s = 0; s < size; ++s)
        map[i+s] = j;
      ++j;
    }
  }
};

}}