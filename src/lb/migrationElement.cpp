#include <lb/migrationElement.h>
#include <system/errors.h>
#include <iostream>

void MigrationElement::set(const MigrationElement::Id &taskId, const MigrationElement::Id &peId) {
  
  //TODO: if concurrent, lock
  _taskToPe[taskId] = peId;
  //TODO: if concurrent, unlock

}

const std::vector<MigrationElement::Id> MigrationElement::mappedTasks() const {
  //TODO: if called multiple times after done setting migrations, this should be static or buffered.
  std::vector<MigrationElement::Id> vector;

  for(auto const& element : _taskToPe)
    vector.push_back(element.first);

  return vector;
}

const MigrationElement::Id MigrationElement::getTaskPE(const MigrationElement::Id &id) const {

  auto PEOfTask = _taskToPe.find(id);
  if(PEOfTask == _taskToPe.end() )
    throw Error::MIGRATION_OUT_OF_BOUNDS;

  return PEOfTask->second;
}