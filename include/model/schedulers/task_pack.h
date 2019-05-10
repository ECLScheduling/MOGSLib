#pragma once

#include <model/policies/task_pack.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class TaskPack
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename C>
class TaskPack {
public:
  using Ctx = C;
  using Id = typename Ctx::Id;
  using Policy = MOGSLib::Policy::TaskPack<MOGSLib::Dependency::Base<Id>>;
  using Schedule = typename Policy::Schedule;

  /**
   *  @brief The method to obtain a task map based on a compact policy.
   **/
  void work(Ctx &ctx) {
    auto &input = ctx.input();
    auto packs = ctx.k();

    Policy::map(ctx.schedule(), input.ntasks(), input.npus(), packs);
  }

};

}}