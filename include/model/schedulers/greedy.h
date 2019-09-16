#pragma once

#include <model/policies/greedy.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class Greedy
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief Class that represents a scheduler which utilizes a greedy heuristic to output a task map.
 **/
template<typename C>
class Greedy {
public:
  using Ctx = C;
  using Id = typename Ctx::Id;
  using Load = typename Ctx::Load;
  using Policy = MOGSLib::Policy::Greedy<MOGSLib::Dependency::WorkloadAware<Id,Load>>;
  using Schedule = typename Policy::Schedule;

  /**
   *  @brief The method to obtain a task map based on a greedy heuristic.
   **/
  void work(Ctx &ctx) {
    auto &input = ctx.input();
    Policy::map(ctx.schedule(), input.task_workloads(), input.pu_workloads());
  }
};

}}
