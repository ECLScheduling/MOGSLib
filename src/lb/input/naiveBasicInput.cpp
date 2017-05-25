#include <lb/input/naiveBasicInput.h>
#include <system/errors.h>

const std::set<NaiveBasicInput::Id> &NaiveBasicInput::getPEsIds() const {
  return _PEs;
}

const NaiveBasicInput::Load& NaiveBasicInput::getTaskLoad(const NaiveBasicInput::Id &taskId) const {
  auto setIt = _tasks.find(taskId);

  if(setIt == _tasks.end()) {
    throw Error::INVALID_INPUT_ACCESS;
  }

  return setIt->second;
}

//TODO: If this method is called multiple times, it should be buffered or saved to avoid calculating the same set over and over.
const std::set<NaiveBasicInput::Id> NaiveBasicInput::getTasksIds() const {
  std::set<NaiveBasicInput::Id> taskIdSet;

  for(auto const& element : _tasks)
    taskIdSet.insert(element.first);

  return taskIdSet;
}