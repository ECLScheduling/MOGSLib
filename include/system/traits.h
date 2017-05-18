#pragma once

#include <system/types.h>
#include <cstdint>
#include <map>

template<typename T>
struct Traits {};

template<>
struct Traits<BasicInput> {
  typedef uint_fast32_t Load;
  typedef uint_fast32_t TaskId;
};

