#pragma once

#include <rts/charm.h>
#include <rts/charm.ipp>

#include <schedulers/greedy.h>

#include <concepts/concrete/basic_scheduler_input.h>
#include <concepts/init/charm/basic_scheduler_input.ipp>


namespace MOGSLib {

template<typename Tuple, unsigned Index, unsigned ... Indexes>
struct ConceptInitializer {
  static void tuple_init(Tuple &tuple) {
    ConceptInitializer<Tuple, Index>::tuple_init(tuple);
    ConceptInitializer<Tuple, Indexes...>::tuple_init(tuple);
  }
};

template<typename Tuple, unsigned Index>
struct ConceptInitializer<Tuple, Index> {
  static bool initialized;
  static void tuple_init(Tuple &tuple) {
    if(!initialized)
      std::get<Index>(tuple).init();
    initialized = true;
  }
};

template<typename Tuple, unsigned Index>
bool ConceptInitializer<Tuple, Index>::initialized;

/**
 * @brief This structure assembles MOGSLibs components into a Scheduler collection that can be use within a selected RTS.
 * @details These definitions are generated automatically when executing scripts/configure.py with proper parameters
 */
struct SchedulerCollection {
  using RTS = MOGSLib::Abstraction::RTS<MOGSLib::TargetSystem>;

  template<template<typename ... Concepts> typename Sched, typename ... Concepts>
  struct CompleteScheduler {
    using Scheduler = Sched<Concepts...>;
    using ConceptTuple = std::tuple<Concepts *...>

    std::unique_pointer<Scheduler> scheduler;
    std::unique_pointer<ConceptTuple> concepts;

    TaskMap init_and_work(Concepts *... concepts) {
      sched.init(concepts...);
      return sched.work();
    }

    TaskMap work() {
      return sched.work();
    }

    void clean() {
      ConceptInitializer<ConceptTuple, std::tuple_elements<ConceptTuple>::value>::clean(concepts);
    }
  };

  using SchedulerTuple = std::tuple<SchedulerTupleDef(Greedy, ConceptDecl(BasicSchedulerInput), ConceptDecl(BasicSchedulerInput), ConceptDecl(BasicSchedulerInput))>;
  using ConceptTuple = std::tuple<ConceptDecl(BasicSchedulerInput)>

  SchedulerTuple schedulers;
  ConceptTuple concepts;

  void TaskMap schedule(std:string &scheduler_name) {
		ScheduleSnippet(0)
    return nullptr;
  }
};

}