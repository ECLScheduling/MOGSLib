#pragma once

#include <policies/compact.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class Compact
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename Ctx>
class Compact {
public:
  using Id = typename Ctx::Index;
  using Policy = MOGSLib::Policy::Compact<Id>;

  /**
   *  @brief The method to obtain a task map based on a compact policy.
   **/
  auto work() {
    auto data = Ctx::basic_input();
    auto schedule = Policy::Schedule(data.ntasks());
    
    Policy::map(schedule, data.ntasks(), data.npus());
    return map;
  }

};

}}