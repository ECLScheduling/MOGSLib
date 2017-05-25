#pragma once

#include <lb/input/basicInput.h>
#include <vector>
#include <map>

/**
 * This class serves as the implementation of a load balancer's input which only contains the simplest information available, the number of PEs and each task's load.
 */
class NaiveBasicInput : public BasicInput {
protected:

  /**
   * A set of ids for each PE.
   */
  const std::set<Id> _PEs;

  /**
   * A map linking a task's id to a task's load.
   */
  const std::map<Id, Load> _tasks;

public:

  /**
   * Creates a NaiveBasicInput object to be used as the input of a load balancer.
   * @param peIds A set of ids to identify each PE in the system.
   * @param tasks A map linking an id to a load, representing the tasks in the system.
   */
  NaiveBasicInput(const std::set<Id> &peIds, const std::map<Id, Load> &tasks) : _PEs(peIds), _tasks(tasks) {}

  /**
   * @return All the PEs Ids.
   */
  const std::set<Id> &getPEsIds() const;

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
  const std::set<Id> getTasksIds() const;
};

