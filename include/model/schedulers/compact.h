#pragma once

#include <model/policies/compact.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class Compact
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename C>
class Compact {
public:
  using Ctx = C;
  using Id = typename Ctx::Id;
  using Policy = MOGSLib::Policy::Compact<MOGSLib::Dependency::Base<Id>>;
  using Schedule = typename Policy::Schedule;

  /**
   *  @brief The method to obtain a task map based on a compact policy.
   **/
  void work(Ctx &ctx) {
    auto &input = ctx.input();
    Policy::map(ctx.schedule(), input.ntasks(), input.npus());
  }

};

}}