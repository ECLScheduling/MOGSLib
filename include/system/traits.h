#pragma once

#include <system/types.h>
#include <cstdint>
#include <map>

template<typename T>
struct Traits {};

template<>
struct Traits<BasicInput> {
  /**
   * The type definition that will serve to quantify a task's load value for the BasicInput class.
   */
  typedef uint_fast32_t Load;

  /**
   * The type definition that will serve to identify tasks and PEs for the BasicInput class.
   */
  typedef uint_fast32_t Id;
};

template<>
struct Traits<MigrationElement> {
  
  /**
   * The type definition that will serve to identify tasks and PEs of the system for the MigrationElement class.
   */
  typedef uint_fast32_t Id;
};