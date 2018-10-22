#pragma once

@RTS_INCLUDES@
@SCHED_INCLUDES@
@CONCEPT_INCLUDES@
namespace MOGSLib {

#define SchedulerDecl(Name) MOGSLib::Scheduler::Name
#define ConceptDecl(Name) MOGSLib::Concept::Name
#define SchedulerTupleDef(SchedName, ...) CompleteScheduler<SchedName, ##__VA_ARGS__>
  /** TODO: The next line is unsupported by some compilers. More study in this might make it more portable. As of now ##__VA_ARGS__ must do. **/
//#define SchedulerTupleDef(SchedName, ...) CompleteScheduler<MOGSLib::Scheduler::SchedName __VA_OPT__(,) __VA_ARGS__>

#define ScheduleSnippet(SchedId) \
if(scheduler_name.compare(SchedulerTraits< std::tuple_element<SchedId, SchedulerTuple>::type::Scheduler::scheduler_type() >::name()) == 0) \
    return std::get<SchedId>(schedulers).init_and_work();

#define TupleGetSnippet(ConceptName, ConceptIndex) \
template<bool spec> \
struct TupleGet<ConceptName, spec> { \
  static ConceptName* get() { \
    ConceptInitializer<type, ConceptIndex>::init(ConceptTuple::concepts); \
    return &std::get<ConceptIndex>(ConceptTuple::concepts); } \
};

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
    if(!initialized) {
      Driver<typename std::tuple_element<Index,Tuple>::type, TargetSystem>::init(std::get<Index>(tuple));
      initialized = true;
    }
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

$TUPLE_GET_SPECS$

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

  /**
   * @brief This structure assembles all the components to form a complete scheduler in a given system.
   * @details The assembly is composed of a scheduler and all its dependent concepts already situated in a context.
   * @type Sched The scheduler class with its dependencies expressed.
   * @type Concepts This variadic template argument encompasses all the concrete concepts already parametrized to respect the target RTS/Libraries.
   */
  template<template<typename ... Concepts> typename Sched, typename ... Concepts>
  struct CompleteScheduler {
    using Scheduler = Sched<Concepts...>;

    std::unique_ptr<Scheduler> scheduler;

    /**
     * @brief This method initializes the global scheduler, its concepts and then issues the work call.
     */
    TaskMap init_and_work() {
      scheduler = std::make_unique<Scheduler>();
      scheduler->init(ConceptTuple::get_tuple<Concepts...>());
      return work();
    }

    /**
     * @brief This method calls the work method contained in the global scheduler.
     * @details This method works under the assumption that all the concepts and the scheduler itself is already instantiated and initialized.
     */
    TaskMap work() {
      return scheduler->work();
    }
  };

  using SchedulerTuple = std::tuple<$SCHEDULER_TUPLE$>;
  static SchedulerTuple schedulers;

  /**
   * @brief Evoke a scheduler and its dependencies to obtain a task map.
   * @details Calls the init method of every concept linked to the scheduler and the scheduler's init itself, then call the scheduler's work method.
   * @param scheduler_name The name of the scheduler to be invoked. The names are declared in the scheduler traits.
   */
  static TaskMap schedule(std::string &scheduler_name) {
$SCHEDULE_SNIPPET$
    return nullptr;
  }
};

decltype(SchedulerCollection::ConceptTuple::concepts) SchedulerCollection::ConceptTuple::concepts;
decltype(SchedulerCollection::schedulers) SchedulerCollection::schedulers;

}