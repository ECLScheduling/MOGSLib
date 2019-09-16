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
  void work(Ctx &ctx) {
    auto &input = ctx.input();
    Policy::map(ctx.schedule(), input.ntasks(), input.npus());
  }

};

}}