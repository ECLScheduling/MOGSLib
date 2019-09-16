#pragma once

#include <model/policies/binlpt.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class BinLPT
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief A scheduler which utilizes the binlpt policy to output a workload-aware task map.
 **/
template<typename C>
class BinLPT {
public:
  using Ctx = C;
  using Id = typename Ctx::Id;
  using Load = typename Ctx::Load;
  using Policy = MOGSLib::Policy::BinLPT<MOGSLib::Dependency::WorkloadAware<Id,Load>>;
  using Schedule = typename Policy::Schedule;
  
  /// @brief The method to obtain a schedule based on a binlpt policy.
  void work(Ctx &ctx) {
    auto &input = ctx.input();
    Policy::map(ctx.schedule(), input.task_workloads(), input.pu_workloads(), ctx.nchunks());
  }

};

}}