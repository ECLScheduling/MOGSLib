#include <lb/input/naiveBasicInput.h>
#include <system/errors.h>

inline const NaiveBasicInput::Load& NaiveBasicInput::getTaskLoad(const unsigned long &index) const { 
  if(index > _taskLoads.get()->size())
    throw Error::INPUT_OUT_OF_BOUNDS;
  return _taskLoads.get()->at(index);
}

inline const NaiveBasicInput::TaskId& NaiveBasicInput::getTaskId(const unsigned long &index) const {
  if(index > _taskIds.get()->size())
    throw Error::INPUT_OUT_OF_BOUNDS;
  return _taskIds.get()->at(index); 
}