#ifndef __NAIVE_BASIC_INPUT_H__
#define __NAIVE_BASIC_INPUT_H__

#include <lb/input/basicInput.h>
#include <memory>

/**
 * This class serves as the implementation of a load balancer's input which only contains the simplest information available, the number of PEs and each task's load.
 */
class NaiveBasicInput : public BasicInput {
public:
  typedef std::shared_ptr<const Load> LoadArrayConst;
  typedef std::shared_ptr<Load> LoadArray;

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
  const LoadArrayConst _taskLoads;

public:

  /**
   * Creates a NaiveBasicInput object to be used as the input of a load balancer.
   * @param peCount The number of PEs in the environment.
   * @param taskCount The number of tasks in the environment.
   * @param taskLoads The load of each task in the environment.
   */
  NaiveBasicInput(const unsigned int &peCount, const unsigned int &taskCount, const LoadArrayConst taskLoads ) : _peCount(peCount), _taskCount(taskCount) , _taskLoads(taskLoads){}

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
   * @return Get a task's load value, which is identified by it's index.
   */
  inline const BasicInput::Load& getTaskLoad(const unsigned long &index) const { return _taskLoads.get()[index]; } 
};

#endif