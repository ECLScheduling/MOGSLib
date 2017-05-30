#pragma once

#include <system/traits.h>
#include <set>

/**
 * The abstract class which intends to be the simplest possible input to a load balancer, carrying only the PEs ids and each task's load and id.
 */
class BasicInput {
public:
  typedef Traits<BasicInput>::Load Load;
  typedef Traits<BasicInput>::Id Id;
  typedef Traits<BasicInput>::SetOfId SetOfId;

  /**
   * @return All the PEs Ids.
   */
  virtual const SetOfId &getPEsIds() const = 0;

  /**
   * Method to obtain a specific task's load.
   * @param taskId The task's id.
   * @return The task's load.
   */
  virtual const Load& getTaskLoad(const Id &taskId) const = 0;

  /**
   * Get the task's set of ids.
   * @return Get all the task's ids.
   */
  virtual const SetOfId getTasksIds() const = 0;

};

