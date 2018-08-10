#pragma once

#include <rts/openmp.h>
#include <rts/openmp.ipp>

#include <schedulers/greedy.h>
#include <binders/greedy_binder.h>

#include <concepts/initializer/openmp/basic_scheduler_input_init.h>
#include <concepts/initializer/openmp/basic_scheduler_input_init.ipp>

namespace MOGSLib {

/**
 * @brief This structure defines concrete concepts, schedulers and the other specifications such as the target system where the library will be attached to.
 * @details These definitions are generated automatically when executing scripts/configure.py with proper parameters
 */
struct Definitions {
  using RTS = MOGSLib::Abstraction::RTS<MOGSLib::TargetSystem>;

  template<typename T>
  using Initializer = MOGSLib::Abstraction::Initializer<RTS::id, T>;

	using Adapter0 = MOGSLib::Adapter::BasicSchedulerInput;
  using Scheduler = MOGSLib::Scheduler::Greedy<MOGSLib::Adapter::BasicSchedulerInput>;

  using Binder = MOGSLib::Abstraction::Binder<Scheduler>;
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