#pragma once

#include <system/type_definitions.h>

#include <abstractions/initializer.h>
#include <abstractions/binder.h>

@RTS_INCLUDES@
@SCHED_INCLUDES@
@CONCEPT_INCLUDES@
namespace MOGSLib {

/**
 * @brief This structure defines concrete concepts, schedulers and the other specifications such as the target system where the library will be attached to.
 * @details These definitions are generated automatically when executing scripts/configure.py with proper parameters
 */
struct Definitions {
  using RTS = MOGSLib::Abstraction::RTS<MOGSLib::TargetSystem>;

  template<typename T>
  using Initializer = MOGSLib::Abstraction::Initializer<system, T>;

  template<typename T>
  using Binder = MOGSLib::Abstraction::Binder<T>;

@ADAPTERS_TYPEDEFS@
  using Scheduler = MOGSLib::Scheduler::@SCHED_NAME@<@SCHED_ADAPTERS@>;
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