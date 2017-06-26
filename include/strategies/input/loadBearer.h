#pragma once

#include <system/traits.h>

/**
 * A simple modelling of a running Task in the system.
 */
struct LoadBearer {
  typedef Traits<TaskSimplified>::Load Load;
  typedef Traits<TaskSimplified>::Id Id;

  /**
   * The task's id.
   */
  Id id;

  /**
   * The task's load.
   */
  Load load;

  Task() {}
  Task(Id &anId, Load &aLoad ) {
    id = anId;
    load = aLoad;
  }

  /**
   * A comparator that checks the load of each load bearer to decide which is greater.
   */
  const bool operator >(const LoadBearer &other) const {
    return load > other.load;
  }

};