#pragma once

@RTS_INCLUDES@
@SCHED_INCLUDES@
@CONCEPT_INCLUDES@

#define SchedulerDecl(Name) MOGSLib::Scheduler::Name
#define ConceptDecl(Name) MOGSLib::Concept::Name
/** TODO: The next line is unsupported by some compilers. More study in this might make it more portable. As of now ## does the trick. **/
//#define SchedulerTupleDef(SchedName, ...) CompleteScheduler<MOGSLib::Scheduler::SchedName __VA_OPT__(,) __VA_ARGS__>
#define SchedulerTupleDef(SchedName, ...) CompleteScheduler<SchedulerDecl(SchedName), ##__VA_ARGS__>

#define ScheduleSnippet(SchedId) \
if(scheduler_name.compare(SchedulerTraits<typename std::tuple_element<SchedId, SchedulerTuple>::type::SchedulerType)>::name) {\
  if(init)\
    return std::get<SchedId>(schedulers).init_and_work();\
  return std::get<SchedId>(schedulers).work();\
}

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