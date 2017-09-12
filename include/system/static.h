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

namespace static_functions {

constexpr bool const_string_equal( char const* lhs, char const* rhs )
{
    while (*lhs || *rhs)
        if (*lhs++ != *rhs++)
            return false;
    return true;
}

}