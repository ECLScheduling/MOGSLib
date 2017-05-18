#pragma once

#include <lb/input/basicInput.h>
#include <memory>
#include <vector>

/**
 * This class serves as the implementation of a load balancer's input which only contains the simplest information available, the number of PEs and each task's load.
 */
class NaiveBasicInput : public BasicInput {
public:
  typedef std::shared_ptr<std::vector<TaskId> > TaskIdSetPtr;
  typedef std::shared_ptr<std::vector<Load> > TaskLoadSetPtr;

protected:

  /**
   * The processing element count in the environment.
   */
  const unsigned int _peCount;

  /**
   * The task count in the environment.
   */
  const unsigned int _taskCount;

  /**
   * The array of task's load.
   */
  const TaskLoadSetPtr _taskLoads;

  /**
   * The array of task's id.
   */
  const TaskIdSetPtr _taskIds;

public:

  /**
   * Creates a NaiveBasicInput object to be used as the input of a load balancer.
   * @param peCount The number of PEs in the environment.
   * @param taskCount The number of tasks in the environment.
   * @param taskLoads The load of each task in the environment.
   */
  NaiveBasicInput(const unsigned int &peCount, const unsigned int &taskCount, const TaskLoadSetPtr taskLoads, const TaskIdSetPtr taskIds  ) : _peCount(peCount), _taskCount(taskCount) , _taskLoads(taskLoads), _taskIds(taskIds){}

  /**
   * @return Get the ammount of processing elements in this input.
   */
  inline const unsigned int& getPECount() const { return _peCount; }

  /**
   * @return Get the ammount of tasks in this input.
   */
  inline const unsigned int& getTaskCount() const { return _taskCount; }

  /**
   * @param index the index of a specific task.
   * @return Get a task's load value, which is identified by it's element index.
   */
  inline const BasicInput::Load& getTaskLoad(const unsigned long &index) const;

  /**
   * @param index the index of a specific task.
   * @return Get a task's id value, which is identified by it's element index.
   */
  inline const TaskId& getTaskId(const unsigned long &index) const;
};

