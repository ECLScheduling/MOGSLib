#pragma once

#include <vector>
#include <abstractions/scheduler.h>

#include <system/option.h>

#include <schedulers/round_robin.h>

#include <concepts/concrete/basic_scheduler_input.h>

namespace MOGSLib {

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