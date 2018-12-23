#pragma once

#include <policies/binlpt.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class BinLPT
 *  @tparam Ctx The context where the scheduler will be applied to.
 *  @brief A scheduler which utilizes the binlpt policy to output a workload-aware task map.
 **/
template<typename Ctx>
class BinLPT {
public:
  using Id = typename Ctx::Index;
  using Load = typename Ctx::Load;
  using Policy = MOGSLib::Policy::BinLPT<Id, Load>;
  
  /// @brief The method to obtain a schedule based on a binlpt policy.
  auto work() {
    auto data = Ctx::workload_input();
    auto chunks = Ctx::chunks();
    auto schedule = Policy::Schedule(data.ntasks());
    
    Policy::map(schedule, data.tasks(), data.pus(), chunks);
    return schedule;
  }

};

}}