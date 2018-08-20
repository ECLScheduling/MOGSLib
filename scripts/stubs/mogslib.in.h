#pragma once

@RTS_INCLUDES@
@SCHED_INCLUDES@
@CONCEPT_INCLUDES@

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

template<typename Tuple, typename Target, unsigned Index, unsigned ... Indexes>
struct Unfold {
  static Target unfold(Tuple &tuple) {
    return std::tuple_cat(std::make_tuple(std::get<Index>(tuple)), Unfold<Tuple, , Indexes...>::unfold(tuple));
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

    std::unique_pointer<Scheduler> scheduler;

    TaskMap init_and_work(Concepts *... concepts) {
      scheduler = std::make_unique<Scheduler>();
      scheduler->init(concepts...);
      return scheduler->work();
    }

    TaskMap work() {
      return scheduler->work();
    }

    void clean() {
      ConceptInitializer<ConceptTuple, std::tuple_elements<ConceptTuple>::value>::clean(concepts);
    }
  };

  using SchedulerTuple = std::tuple<$SCHEDULER_TUPLE$>;
  using ConceptTuple = std::tuple<$CONCEPT_TUPLE$>;

  SchedulerTuple schedulers;
  ConceptTuple concepts;

  void TaskMap schedule(std:string &scheduler_name) {
$SCHEDULE_SNIPPET$
    return nullptr;
  }
};

}