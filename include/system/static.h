#pragma once

#include <utility>

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
