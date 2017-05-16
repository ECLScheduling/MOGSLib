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

  const unsigned int _peCount;
  const unsigned int _taskCount;
  const LoadArrayConst _taskLoads;

public:

  NaiveBasicInput(const unsigned int &PECount, const unsigned int &TaskCount, const LoadArrayConst taskLoads ) : _peCount(PECount), _taskCount(TaskCount) , _taskLoads(taskLoads){}

  inline const unsigned int& getPECount() const { return _peCount; }
  inline const unsigned int& getTaskCount() const { return _taskCount; }

  inline const BasicInput::Load& getTaskLoad(const unsigned long &index) const { return _taskLoads.get()[index]; } 
};

#endif