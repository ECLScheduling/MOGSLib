#pragma once

#include <system/traits.h>
#include <vector>

/**
 * This class is a DOD (Data Oriented Design) implementation of a migration set that is given as output of a LB.
 */
class MigrationElement {
public:
  typedef Traits<MigrationElement>::Id Id;
  typedef std::vector<Id>::size_type IndexType;
  
protected:
  /**
   * A map of task's Ids to PE's ids.
   */
  std::map<Id, Id> _taskToPE;

public:

  /**
   * @return The number of migration elements.
   */
  inline const IndexType count() const { return _taskToPE.size(); }

  /**
   * Adds a new migration element to the Migration's set.
   * @param taskId The taskId which will be migrated.
   * @param peId The peId which will be migrated.
   */
  void set(const Id &taskId, const Id &peId);

  /**
   * Get the taskIds that will need to be migrated.
   * @return The taskIds of the tasks that needs migration.
   */
  const std::vector<Id> mappedTasks() const;

  /**
   * Get the peId of a task that will migrate.
   * @param id The id of the task that will migrate.
   * @throw MIGRATION_TASK_INEXISTENT if tried to access a migration that is not contained in the list.
   * @return The target peId of a task migration. 
   */  
  const Id getTaskPE(const Id &id) const;
};

