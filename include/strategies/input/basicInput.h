#pragma once

#include <set>

/**
 * The abstract class which intends to be the simplest possible input to a load balancer, carrying only the PEs ids and each task's load and id.
 */
class BasicInput {
public:
  typedef Traits<BasicInput>::Load Load;
  typedef Traits<BasicInput>::Id Id;
  typedef Traits<BasicInput>::Task Task;
  typedef Traits<BasicInput>::SetOfTasks SetOfTasks;
  typedef Traits<BasicInput>::SetOfId SetOfId;

  /**
   * @return All the PEs Ids.
   */
  virtual const SetOfId &getPEs() const = 0;

  /**
   * @return Get the set of tasks.
   */
  virtual const SetOfTasks getTasks() const = 0;

};

/**
 * The abstract class that extends the basic input with an additional starting load information.
 */
class WithStartingLoad {
public:

  /**
   * Method to get an initial PE Load.
   * @param peId The id of the PE in the system.
   * @return The Load of the PE.
   */
  virtual const BasicInput::Load& getPELoad(const BasicInput::Id &PEId) const = 0;
};