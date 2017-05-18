#ifndef __TRAITS_LB_H__
#define __TRAITS_LB_H__

#include <system/types.h>
#include <map>

template<typename T>
struct Traits {};

template<>
struct Traits<BasicInput> {

  /**
   * The type definition that will serve to quantify a task's load value for the BasicInput class.
   */
  typedef unsigned int Load;

  /**
   * The type definition that will serve to identify tasks for the BasicInput class.
   */
  typedef unsigned int TaskId;
};

template<>
struct Traits<MigrationElement> {
  
  /**
   * The type definition that will serve to identify tasks and PEs of the system for the MigrationElement class.
   */
  typedef unsigned int Id;
};

#endif