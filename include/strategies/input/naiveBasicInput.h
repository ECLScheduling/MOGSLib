#pragma once

#include "basicInputTaskContainer.h"
#include <system/errors.h>

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
  NaiveBasicInput(const SetOfTasks &tasks, const SetOfId &PEIds) : BasicInputTaskContainer(tasks), _PEs(PEIds) {}

  virtual ~NaiveBasicInput() {}

  /**
   * @return All the PEs Ids.
   */
  const SetOfId &getPEs() const {
    return _PEs;
  }
  
};