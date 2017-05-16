#include <lb/migrationElement.h>
#include <system/errors.h>

void MigrationElement::setMigration(const unsigned int &taskId, const unsigned int &peId) {
  //TODO: if concurrent, lock
  const IndexType index = _taskId.size() + 1;
  //TODO: if concurrent, unlock

  _taskId[index] = taskId;
  _peId[index] = peId;
}

const unsigned int MigrationElement::taskId(const MigrationElement::IndexType &index) const {

  if(index >= _taskId.size()) {
    throw Error::MIGRATION_OUT_OF_BOUNDS;
  }
  return _taskId[index];
}

const unsigned int MigrationElement::peId(const MigrationElement::IndexType &index) const {

  if(index >= _peId.size()) {
    throw Error::MIGRATION_OUT_OF_BOUNDS;
  }
  return _peId[index];
}