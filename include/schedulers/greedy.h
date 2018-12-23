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
  using Id = typename Ctx::Index;
  using Load = typename Ctx::Load;
  using Policy = MOGSLib::Policy::Greedy<Id, Load>;

  /**
   *  @brief The method to obtain a task map based on a greedy heuristic.
   **/
  auto work() {
    auto data = Ctx::workload_input();
    auto schedule = Policy::Schedule(data.ntasks());
    
    Policy::map(schedule, data.tasks(), data.pus());
    return map;
  }
};

}}
