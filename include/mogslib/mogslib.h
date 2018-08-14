#pragma once

#include <mogslib/rts/charm.h>
#include <mogslib/rts/charm.ipp>

#include <schedulers/greedy.h>

#include <concepts/concrete/basic_scheduler_input.h>
#include <concepts/init/charm/basic_scheduler_input.ipp>

namespace MOGSLib {

/**
 * @brief This structure defines concrete concepts, schedulers and the other specifications such as the target system where the library will be attached to.
 * @details These definitions are generated automatically when executing scripts/configure.py with proper parameters
 */
struct Definitions {
  using RTS = MOGSLib::Abstraction::RTS<MOGSLib::TargetSystem>;
	using Adapter0 = MOGSLib::Concept::BasicSchedulerInput;
  using Scheduler = MOGSLib::Scheduler::Greedy<MOGSLib::Concept::BasicSchedulerInput>;
};

/*
struct Schedulers {
  using SchedulerPtr = Abstraction::Scheduler*;
  
  static std::vector<SchedulerPtr> list;

  static inline Optional::Option<SchedulerPtr>* get_by_name(const std::string &name) {
    for(auto sched : list)
      if(sched->name.compare(name) == 0)
        return new Optional::Some<SchedulerPtr>(sched);
    return new Optional::None<SchedulerPtr>();
  }
};

std::vector<Schedulers::SchedulerPtr> Schedulers::list = { new Scheduler::RoundRobin<Adapter::BasicSchedulerInput>() };

}
*/

}