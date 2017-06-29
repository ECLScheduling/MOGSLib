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

  std::vector<PE*> PEs;
  std::vector<Task*> tasks;

public:

  /**
   * A constructor that initializes the input with empty vectors.
   */
  MinimalParallelInput() {}

  /**
   * Empty deconstructor for warning suppressions.
   */
  virtual ~MinimalParallelInput() {}

  /**
   * Adds a PE to the input.
   * @param aPE A pointer to the PE's data.
   */
  void addPE(PE *aPE) {
    PEs.push_back(aPE);
  }

  /**
   * Adds a task to the input.
   * @param aTask A pointer to the task's data.
   */
  void addTask(Task *aTask) {
    tasks.push_back(aTask);
  }

  /**
   * @return A pointer to an array of PEs.
   */
  const PE *getPEs() const {
    return &PEs[0];
  }

  /**
   * @return The ammount of PEs in this input.
   */
  const unsigned int PECount() {
    return PEs.size();
  }

  /**
   * @return A pointer to an array of tasks.
   */
  const Task *getTasks() const {
    return &tasks[0];
  }

  /**
   * @return The ammount of Tasks in this input.
   */
  const unsigned int taskCount() {
    return tasks.size();
  }

};