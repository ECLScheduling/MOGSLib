#pragma once

namespace MOGSLib { namespace Policy {

/**
 *  @class Compact
 *  @brief A workload-unaware policy that divides the tasks into equally sized groups and assign them to PUs.
 *  
 *  This policy groups tasks that are adjacent in ordering.
 *  This characteristic might result in better cache locality in systems like OpenMP.
 */
class Compact {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  /**
   *  @brief Divide the tasks into groups and assign them to PUs in increasing index.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   */
  static void map(TaskMap &map, const Index &ntasks, const Index &npus) {
    auto size = ntasks/npus;
    decltype(ntasks) j = 0;
    for(decltype(ntasks) i = 0; i < ntasks; i += size){
      for(Index s = 0; s < size; ++s)
        map[i+s] = j;
      ++j;
    }
  }
};

}}