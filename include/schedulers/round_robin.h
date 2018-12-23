#pragma once

#include <policies/round_robin.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class RoundRobin
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief Class that represents a scheduler which utilizes a round robin heuristic to output a task map.
 **/
template<typename Ctx>
class RoundRobin {
public:
  using Id = typename Ctx::Index;
  using Policy = MOGSLib::Policy::RoundRobin<Id>;
  
  /**
   *  @brief The method to obtain a task map based on a roundrobin heuristic.
   **/
  auto work() {
    auto data = Ctx::basic_input();
    auto schedule = Policy::Schedule(data.ntasks());
    
    Policy::map(schedule, data.ntasks(), data.npus());
    return map;
  }

};

}}