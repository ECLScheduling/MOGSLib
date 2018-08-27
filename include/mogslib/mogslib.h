#pragma once

#include <rts/charm.h>
#include <rts/charm.ipp>

@SCHED_INCLUDES@
@CONCEPT_INCLUDES@

namespace MOGSLib {

/**
 * @brief This static structure is responsible for calling the init method of several Concepts within a tuple of concepts.
 * @type Tuple A tuple of concepts concrete definition.
 * @type Index The index passed as template parameter to std::get.
 * @type Indice The indice of the next concept's init calls.
 */
template<typename Tuple, unsigned Index, unsigned ... Indice>
struct ConceptInitializer {
  static void tuple_init(Tuple &tuple) {
    ConceptInitializer<Tuple, Index>::tuple_init(tuple);
    ConceptInitializer<Tudice...>::tuple_init(tuple);
  }
};

/**
 * @brief This specialization of ConceptInitializer is responsible for calling the init method of a single Concept within a tuple of concepts.
 * @details When a concept is initialized by this structure, future calls to its initialization won't invoke the init method of the previously-initialized concept.
 * @type Tuple A tuple of concepts concrete definition.
 * @type Index The index passed as template parameter to std::get.
 */
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

  /**
   * @brief This structure defines a static collection of concepts and eases the access to its members.
   * @details The "type" type is constructed by the precompilation step in MOGSLib as is every TupleGet specialization.
   */
  struct ConceptTuple {
    using type = std::tuple<$CONCEPT_TUPLE$>;
    
    static type concepts;

    /**
     * @brief This static structure serves the purpose of fetching a value from a give type present within the concepts tuple.
     * @details Its not_required boolean value is not required. It is a work-around for full template specializations within a namespace.
     */
    template<typename T, bool not_required = false>
    struct TupleGet {
      static T* get() { return nullptr; }
    };

    $TUPLE_GET_SPECS$ //TupleGetSnippet()

    /**
     * @brief Get a value from the concepts tuple that corresponds to the T type.
     * @details This method utilizes the specialized TupleGet structures that are generated in MOGSLib precompilation step.
     */
    template<typename T>
    static T* get() { return &TupleGet<T>::get(); }

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
      static std::tuple<T*> get() { return std::make_tuple(TupleGet<T>::get()); }
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

    std::unique_pointer<Scheduler> scheduler;

    TaskMap init_and_work() {
      scheduler = std::make_unique<Scheduler>();
      scheduler->init(ConceptTuple::get_tuple<Concepts...>());
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
  static SchedulerTuple schedulers;

  static void TaskMap schedule(std:string &scheduler_name) {
$SCHEDULE_SNIPPET$
    return nullptr;
  }
};

decltype(SchedulerCollection::ConceptTuple::concepts) SchedulerCollection::ConceptTuple::concepts;
decltype(SchedulerCollection::schedulers) SchedulerCollection::schedulers;

}