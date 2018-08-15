#pragma once

#include <rts/charm.h>
#include <rts/charm.ipp>

#include <schedulers/greedy.h>
#include <schedulers/round_robin.h>

#include <concepts/concrete/basic_scheduler_input.h>
#include <concepts/init/charm/basic_scheduler_input.ipp>

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

  using SchedulerTuple = std::tuple<SchedulerTupleDef(Greedy, ConceptDecl(BasicSchedulerInput)),SchedulerTupleDef(RoundRobin, ConceptDecl(BasicSchedulerInput))>;
  static SchedulerTuple schedulers;

  static void TaskMap schedule(const std:string &scheduler_name, const bool &init = true) {
		ScheduleSnippet(0)
		ScheduleSnippet(1)
    return nullptr;
  }
};

decltype(SchedulerCollection::schedulers) SchedulerCollection::schedulers;

}