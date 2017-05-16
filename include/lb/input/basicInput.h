#ifndef __BASIC_INPUT_H__
#define __BASIC_INPUT_H__

#include <system/traits.h>

/**
 * The abstract class which intends to be the simplest possible input to a load balancer, carrying only the number of PEs and each task's load.
 */
class BasicInput {
public:
  typedef Traits<BasicInput>::Load Load;
  typedef Traits<BasicInput>::TaskId TaskId;

  /**
   * @return The number of PE (processing units) in the environment.
   */
  virtual const unsigned int& getPECount() const = 0;

  /**
   * @return The number of Tasks in the environment.
   */
  virtual const unsigned int& getTaskCount() const = 0;

  /**
   * Method to obtain a specific task's load.
   * @param index The index of the task.
   * @return The task's load.
   */
  virtual const Load& getTaskLoad(const unsigned long &index) const = 0;

  /**
   * @param index The index of the task.
   * @return Get the task id in the index.
   */
  virtual const TaskId& getTaskId(const unsigned long &index) const = 0;

};

#endif