#pragma once

#include <system/types.h>
#include <cstdint>
#include <map>
#include <set>

template<typename T>
struct Traits {};

template<>
struct Traits<MigrationElement> {
  
  /**
   * The type definition that will serve to identify tasks and PEs of the system for the MigrationElement class.
   */
  typedef uint_fast32_t Id;

  /**
   * The type definition that will serve to quantify a task's load value for the BasicInput class.
   */
  typedef uint_fast32_t Load;
};

template<>
struct Traits<BasicInput> : Traits<MigrationElement> {

  /**
   * Type definition of the structure used to represent the set of processing elements in the NaiveBasicInput.
   */
  typedef std::set<Id> SetOfId;

  /**
   * Type definition of the structure used to represent the task set in the NaiveBasicInput.
   */
  typedef std::map<Id, Load> LoadMap;
};

template<>
struct Traits<EdgelessGraph> : Traits<MigrationElement> {

  /**
   * Type definition of the weight of a vertex and graph for this tructure.
   */
  typedef uint_fast32_t Weight;
};