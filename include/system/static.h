#pragma once

#include <utility>
#include <type_traits>
#include <tuple>

#define HAS_MEMBER_MACRO(MethodName, TemplateName) \
template <typename T> \
class TemplateName \
{ \
    typedef char Positive; \
    typedef long Negative; \
    template <typename C> static Positive test( decltype(&C::MethodName) ) ; \
    template <typename C> static Negative test(...);    \
public: \
    enum { value = std::is_same<decltype(test<T>(0)), Positive>::value }; \
};

#define HAS_TYPE_MACRO(TypeName, TemplateName) \
template<typename T> \
struct TemplateName \
{ \
  typedef char Positive; \
  typedef long Negative; \
  template <typename C> static Positive test( typename C::TypeName ); \
  template <typename C> static Negative test(...); \
  static const bool value = std::is_same<decltype(test<T>(0)), Positive>::value; \
};

#define BEGIN_NAMESPACE(Name) namespace MOGSLib { namespace Name {
#define END_NAMESPACE }}

#define SchedulerDecl(Name) MOGSLib::Scheduler::Name
#define ConceptDecl(Name) MOGSLib::Concept::Name
/** TODO: The next line is unsupported by some compilers. More study in this might make it more portable. As of now ## does the trick. **/
//#define SchedulerTupleDef(SchedName, ...) CompleteScheduler<MOGSLib::Scheduler::SchedName __VA_OPT__(,) __VA_ARGS__>
#define SchedulerTupleDef(SchedName, ...) CompleteScheduler<SchedName, ##__VA_ARGS__>

#define ScheduleSnippet(SchedId) \
if(scheduler_name.compare(SchedulerTraits<std::tuple_element<SchedId, SchedulerTuple>::type::Scheduler::scheduler_type()>::name()) == 0) \
    return std::get<SchedId>(schedulers).init_and_work();

#define TupleGetSnippet(ConceptName, ConceptIndex) \
template<bool spec> \
struct TupleGet<ConceptName, spec> { \
  static ConceptName* get() { \
    ConceptInitializer<type, ConceptIndex>::init(ConceptTuple::concepts); \
    return &std::get<ConceptIndex>(ConceptTuple::concepts); } \
};
