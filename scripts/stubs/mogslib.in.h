#pragma once

@RTS_INCLUDES@
@SCHED_INCLUDES@
@CONCEPT_INCLUDES@

namespace MOGSLib {

/**
 * @brief This structure assembles MOGSLibs components into a Scheduler collection that can be use within a selected RTS.
 * @details These definitions are generated automatically when executing scripts/configure.py with proper parameters
 */
struct SchedulerCollection {
  using RTS = MOGSLib::Abstraction::RTS<MOGSLib::TargetSystem>;

  template<template<typename ... Concepts> typename Sched, typename ... Concepts>
  struct CompleteScheduler {
    using T = Sched<Concepts...>;

    std::unique_pointer<T> scheduler;

    TaskMap init_and_work(Concepts *... concepts) {
      sched.init(std::make_tuple<Concepts *...>(concepts...));
      return sched.work();
    }

    TaskMap work() {
      return sched.work();
    }
  };

  using SchedulerTuple = std::tuple<$SCHEDULER_TUPLE$>;
  SchedulerTuple schedulers;

  void TaskMap schedule(std:string &scheduler_name) {
$SCHEDULE_SNIPPET$
    return nullptr;
  }
};

}