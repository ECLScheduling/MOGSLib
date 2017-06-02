#include <lb/input/naiveBasicInput.h>
#include <system/errors.h>

inline const BasicInputTaskContainer::Load& NaiveBasicInput::getTaskLoad(const NaiveBasicInput::Id &taskId) const {
  auto setIt = _tasks.find(taskId);

  if(setIt == _tasks.end()) {
    throw Error::INVALID_INPUT_ACCESS;
  }

  return setIt->second;
}

//TODO: If this method is called multiple times, it should be buffered or saved to avoid calculating the same set over and over.
inline const BasicInputTaskContainer::SetOfId NaiveBasicInput::getTasksIds() const {
  NaiveBasicInput::SetOfId taskIdSet;

  for(auto const& element : _tasks)
    taskIdSet.insert(element.first);

  return taskIdSet;
}

inline const NaiveBasicInput::SetOfId &NaiveBasicInput::getPEsIds() const {
  return _PEs;
}