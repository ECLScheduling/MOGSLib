#pragma once

#include <policies/greedy.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class Greedy
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief Class that represents a scheduler which utilizes a greedy heuristic to output a task map.
 **/
template<typename Ctx>
class Greedy {
public:
  using Id = typename Ctx::Id;
  using Load = typename Ctx::Load;
  using Policy = MOGSLib::Policy::Greedy<MOGSLib::Dependency::WorkloadAware<Id,Load>>;
  using Schedule = typename Policy::Schedule;

  /**
   *  @brief The method to obtain a task map based on a greedy heuristic.
   **/
  auto work() {
    auto data = Ctx::input();
    auto schedule = Schedule(data.ntasks());
    
    Policy::map(schedule, data.task_workloads(), data.pu_workloads());
    return schedule;
  }
};

}}
