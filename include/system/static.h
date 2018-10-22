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