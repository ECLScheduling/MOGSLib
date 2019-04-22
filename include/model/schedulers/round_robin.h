#pragma once

#include <model/policies/round_robin.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class RoundRobin
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief Class that represents a scheduler which utilizes a round robin heuristic to output a task map.
 **/
template<typename C>
class RoundRobin {
public:
  using Ctx = C;
  using Id = typename Ctx::Id;
  using Policy = MOGSLib::Policy::RoundRobin<MOGSLib::Dependency::Base<Id>>;
  using Schedule = typename Policy::Schedule;
  
  /**
   *  @brief The method to obtain a task map based on a roundrobin heuristic.
   **/
  auto work(Ctx &ctx) {
    auto &data = ctx.input();
    auto schedule = Schedule(data.ntasks());
    
    Policy::map(schedule, data.ntasks(), data.npus());
    return schedule;
  }

};

}}