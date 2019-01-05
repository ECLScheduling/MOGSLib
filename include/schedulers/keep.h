#pragma once

#include <schedulers/binlpt.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class Keep
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief A scheduler which keeps the schedule saved after the first execution.
 **/
template<typename C>
class Keep {
public:
  using Ctx = C;
  using Id = typename Ctx::Id;
  using Load = typename Ctx::Load;
  using Scheduler = BinLPT<C>;
  using Schedule = typename Scheduler::Schedule;
  
  Scheduler scheduler;

  /// @brief The method to obtain a schedule based on a binlpt policy.
  auto work(Ctx &ctx) {
    if(!ctx.has_schedule())
      ctx.set_schedule(scheduler.work(ctx));
    return ctx.schedule();
  }

};

}}