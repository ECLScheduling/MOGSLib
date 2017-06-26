#include <strategies/input/basicInputTaskContainer.h>
#include <system/errors.h>

const BasicInputTaskContainer::Load& BasicInputTaskContainer::getTaskLoad(const BasicInputTaskContainer::Id &taskId) const {
  auto mapIt = _tasks.find(taskId);

  if(mapIt == _tasks.end()) {
    throw Error::INVALID_INPUT_ACCESS;
  }

  return mapIt->second;
}

//TODO: If this method is called multiple times, it should be buffered or saved to avoid calculating the same set over and over.
const BasicInputTaskContainer::SetOfId BasicInputTaskContainer::getTasksIds() const {
  BasicInputTaskContainer::SetOfId taskIdSet;

  for(auto const& element : _tasks)
    taskIdSet.push_back(element.first);

  return taskIdSet;
}