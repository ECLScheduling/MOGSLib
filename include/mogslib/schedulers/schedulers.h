#pragma once

#include <string>

#include <system/type_definitions.h>
#include <system/types.h>

// #### MOGSLib Includes ####
// MOGSLib RTS data
#include <mogslib/rts/charm.h>
#include <mogslib/rts/charm.ipp>

// MOGSLib Scheduling Strategies
#include <schedulers/round_robin.h>
#include <schedulers/null.h>
#include <mogslib/binders/round_robin_binder.h>

// MOGSLib Concrete Adapters
#include <mogslib/initializers/charm/basic_scheduler_input_init.h>
#include <mogslib/initializers/charm/basic_scheduler_input_init.ipp>
// #### End of MOGSLib Includes ####

namespace MOGSLib {

template<SchedulerTypes Sched>
struct Definitions {
  using RTS = MOGSLib::RTS::Charm;
  static constexpr auto system = RTS::SystemVal;

  template<typename T>
  using Initializer = MOGSLib::Abstraction::Initializer<system, T>;

  template<typename T>
  using Binder = MOGSLib::Abstraction::Binder<T>;
};

template<>
struct Definitions<SchedulerTypes::Greedy> : public Definitions<SchedulerTypes::Null> {
  using ConcreteAdapter1 = Adapter::BasicSchedulerInput;

  using Scheduler = Scheduler::RoundRobin<ConcreteAdapter1>;
};


struct Schedulers {

  static inline Scheduler::TaskMap call_null() { return Scheduler::Null().work(); }

  static inline Scheduler::TaskMap call_round_robin() {
    constexpr auto SchedToken = SchedulerTypes::RoundRobin;
    using Defs = Definitions<SchedToken>;

    // Define concrete concepts
    auto concrete_1 = new Defs::ConcreteAdapter1();

    // Declare scheduler
    Defs::Scheduler scheduler;

    // Initialize concrete adapters
    Defs::Initializer<Defs::ConcreteAdapter1>::init(concrete_1);

    // Bind concrete adapters to concepts.
    Defs::Binder<Defs::Scheduler>::bind(concrete_1, concrete_1);

    // Call Scheduler with specific concepts.
    return scheduler.work();
  }

  static inline Scheduler::TaskMap map(const std::string sched_name) {
    if(sched_name.compare(SchedulerTraits<SchedulerTypes::Greedy>::name) == 0)
        return call_round_robin();
    return call_null();
  }
};

}