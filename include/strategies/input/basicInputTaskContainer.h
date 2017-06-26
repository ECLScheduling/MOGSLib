#pragma once

#include "basicInput.h"

/**
 * A class that envelops the functionality of accessing a map of Task's id to their load value. 
 */
class BasicInputTaskContainer : public BasicInput {

protected:
  
  /**
   * A set of tasks.
   */
  const SetOfTasks _tasks;

public:

  /**
   * Creates the object and initializes the tasks container.
   * @param tasks A set of tasks that represents all the migrateable tasks in the system.
   */
  BasicInputTaskContainer(const SetOfTasks &tasks) : _tasks(tasks) {}

  /**
   * @return The set of tasks this object contains.
   */
  const SetOfId getTasksIds() const {
    return _tasks;
  }

};