#pragma once

#include <lb/input/basicInput.h>
#include <system/errors.h>

/**
 * A class that envelops the functionality of accessing a map of Task's id to their load value. 
 */
class BasicInputTaskContainer : public BasicInput {
public:
  typedef Traits<BasicInput>::LoadMap LoadMap;

protected:
  
  /**
   * A map linking a task's id to a task's load.
   */
  const LoadMap _tasks;

public:

  /**
   * Creates the object and initializes the tasks container.
   * @param tasks A map linking an id to a load, representing the tasks in the system.
   */
  BasicInputTaskContainer(const LoadMap &tasks) : _tasks(tasks) {}

  /**
   * Method to obtain a specific task's load.
   * @param taskId The task's id.
   * @return The task's load.
   */
  const Load& getTaskLoad(const Id &taskId) const;

  /**
   * Get the task's set of ids.
   * @return Get all the task's ids.
   */
  const SetOfId getTasksIds() const;
};

/**
 * This class serves as the implementation of a load balancer's input which only contains the simplest information available, the number of PEs and each task's load.
 */
class NaiveBasicInput : public BasicInputTaskContainer {
protected:

  /**
   * A set of ids for each PE.
   */
  const SetOfId _PEs;

public:

  /**
   * Creates a NaiveBasicInput object to be used as the input of a load balancer.
   * @param peIds A set of ids to identify each PE in the system.
   * @param tasks A map linking an id to a load, representing the tasks in the system.
   */
  NaiveBasicInput(const LoadMap &tasks, const SetOfId &peIds) : BasicInputTaskContainer(tasks), _PEs(peIds) {}

  virtual ~NaiveBasicInput() {}

  /**
   * @return All the PEs Ids.
   */
  const SetOfId &getPEsIds() const;
};