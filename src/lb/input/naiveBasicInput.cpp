#include <lb/input/naiveBasicInput.h>

const NaiveBasicInput::SetOfId &NaiveBasicInput::getPEsIds() const {
  return _PEs;
}

const BasicInputTaskContainer::Load& BasicInputTaskContainer::getTaskLoad(const NaiveBasicInput::Id &taskId) const {
  auto mapIt = _tasks.find(taskId);

  if(mapIt == _tasks.end()) {
    throw Error::INVALID_INPUT_ACCESS;
  }

  return mapIt->second;
}

//TODO: If this method is called multiple times, it should be buffered or saved to avoid calculating the same set over and over.
const BasicInputTaskContainer::SetOfId BasicInputTaskContainer::getTasksIds() const {
  NaiveBasicInput::SetOfId taskIdSet;

  for(auto const& element : _tasks)
    taskIdSet.insert(element.first);

  return taskIdSet;
}