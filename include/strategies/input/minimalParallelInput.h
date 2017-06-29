#pragma once

#include "iminimalParallelInput.h"
#include <vector>

// ######################
//TODO: This includes shouldn't be necessary, but with the current makefile the file's dependencies must be explicitily stated like so... In the event of changing the type of PEs / Task types in the traits file, those includes would need to be changed. That's an error for another time of the framework though.
#include <structures/simplePE.h>
#include <structures/simpleTask.h>
// ######################

/**
 * An implementation of the interface for the minimal parallel input.
 */
class MinimalParallelInput : public IDefaultMinimalParallelInput {

protected:

  PE* const _PEs;
  Task* const _tasks;

  const unsigned int _PECount;
  const unsigned int _taskCount;

public:

  /**
   * A constructor that initializes all the input variables.
   * @param PEs The pointer to an array of PEs.
   * @param tasks The pointer to an array of tasks.
   * @param PECount The number of elements in PEs.
   * @param taskCount The number of elements in taskCount
   */
  MinimalParallelInput(PE * const PEs, Task * const tasks, const unsigned int &PECount, const unsigned int &taskCount) : _PEs(PEs), _tasks(tasks), _PECount(PECount), _taskCount(taskCount) {}

  /**
   * Empty deconstructor for warning suppressions.
   */
  virtual ~MinimalParallelInput() {}

  /**
   * @return A pointer to an array of PEs.
   */
  PE * const getPEs() {
    return _PEs;
  }

  /**
   * @return The ammount of PEs in this input.
   */
  const unsigned int PECount() {
    return _PECount;
  }

  /**
   * @return A pointer to an array of tasks.
   */
  Task * const getTasks() {
    return _tasks;
  }

  /**
   * @return The ammount of Tasks in this input.
   */
  const unsigned int taskCount() {
    return _taskCount;
  }

};