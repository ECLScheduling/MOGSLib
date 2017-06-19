#include <strategies/migrationElement.h>
#include <system/errors.h>
#include <iostream>

void MigrationElement::set(const MigrationElement::Id &taskId, const MigrationElement::Id &PEId) {
  
  //TODO: if concurrent, lock
  _taskToPE[taskId] = PEId;
  //TODO: if concurrent, unlock

}

const std::vector<MigrationElement::Id> MigrationElement::mappedTasks() const {
  //TODO: if called multiple times after done setting migrations, this should be static or buffered.
  std::vector<MigrationElement::Id> vector;

  for(auto const& element : _taskToPE)
    vector.push_back(element.first);

  return vector;
}

const MigrationElement::Id MigrationElement::getTaskPE(const MigrationElement::Id &id) const {

  auto PEOfTask = _taskToPE.find(id);
  if(PEOfTask == _taskToPE.end() )
    throw Error::MIGRATION_INVALID_TASK;

  return PEOfTask->second;
}