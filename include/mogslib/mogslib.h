#pragma once

#include <rts/charm.h>
#include <rts/charm.ipp>

#include <schedulers/round_robin.h>

#include <concepts/concrete/basic_scheduler_input.h>
#include <concepts/init/charm/basic_scheduler_input.ipp>


namespace MOGSLib {

/**
 * @brief This specialization of ConceptInitializer is responsible for calling the init method of a single Concept within a tuple of concepts.
 * @details When a concept is initialized by this structure, future calls to its initialization won't invoke the init method of the previously-initialized concept.
 * @type Tuple A tuple of concepts concrete definition.
 * @type Index The index passed as template parameter to std::get.
 */
template<typename Tuple, unsigned Index>
struct ConceptInitializer {
  static bool initialized;
  static void init(Tuple &tuple) {
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

  /**
   * @brief This structure defines a static collection of concepts and eases the access to its members.
   * @details The "type" type is constructed by the precompilation step in MOGSLib as is every TupleGet specialization.
   */
  struct ConceptTuple {
    using type = std::tuple<ConceptDecl(BasicSchedulerInput)>;
    
    static type concepts;

    /**
     * @brief This static structure serves the purpose of fetching a value from a give type present within the concepts tuple.
     * @details Its not_required boolean value is not required. It is a work-around for full template specializations within a namespace.
     */
    template<typename T, bool not_required = false>
    struct TupleGet {
      static T* get() { return nullptr; }
    };

    TupleGetSnippet(ConceptDecl(BasicSchedulerInput), 0) //TupleGetSnippet()

    /**
     * @brief Get a value from the concepts tuple that corresponds to the T type.
     * @details This method utilizes the specialized TupleGet structures that are generated in MOGSLib precompilation step.
     */
    template<typename T>
    static T* get() { return TupleGet<T>::get(); }

    /**
     * @brief This structure returns a subtuple of the type tuple containing pointers to its values.
     * @details This structure makes use of the TupleGet member structure to construct its output.
     */
    template<typename T, typename ... Ts>
    struct SubTupleGet {
      static std::tuple<T*, Ts *...> get() { return std::tuple_cat(SubTupleGet<T>::get(), SubTupleGet<Ts...>::get()); }
    };

    /**
     * @brief This is a specialization of the SubTupleGet structure that returns a tuple of size 1 of a concept contained in the concepts tuple.
     * @details This is required to prevent an infinite loop of get() function calls as SubTupleGet is recursive.
     */
    template<typename T>
    struct SubTupleGet<T> {
      static std::tuple<T*> get() { return std::make_tuple(ConceptTuple::get<T>()); }
    };

    /**
     * @brief Creates a sub-tuple of pointer to concepts contained in the concepts tuple.
     * @details This method uses the SubTupleGet member structures to construct the output.
     */
    template<typename ... T>
    static auto get_tuple() { return SubTupleGet<T...>::get(); }
  };

  template<template<typename ... Concepts> typename Sched, typename ... Concepts>
  struct CompleteScheduler {
    using Scheduler = Sched<Concepts...>;

    std::unique_ptr<Scheduler> scheduler;

    TaskMap init_and_work() {
      scheduler = std::make_unique<Scheduler>();
      scheduler->init(ConceptTuple::get_tuple<Concepts...>());
      return scheduler->work();
    }

    TaskMap work() {
      return scheduler->work();
    }
  };

  using SchedulerTuple = std::tuple<SchedulerTupleDef(SchedulerDecl(RoundRobin), ConceptDecl(BasicSchedulerInput), ConceptDecl(BasicSchedulerInput))>;
  static SchedulerTuple schedulers;

  /**
   * @brief Evoke a scheduler and its dependencies to obtain a task map.
   * @details Calls the init method of every concept linked to the scheduler and the scheduler's init itself, then call the scheduler's work method.
   * @param scheduler_name The name of the scheduler to be invoked. The names are declared in the scheduler traits.
   */
  static TaskMap schedule(std::string &scheduler_name) {
		ScheduleSnippet(0)
    return nullptr;
  }
};

decltype(SchedulerCollection::ConceptTuple::concepts) SchedulerCollection::ConceptTuple::concepts;
decltype(SchedulerCollection::schedulers) SchedulerCollection::schedulers;

}