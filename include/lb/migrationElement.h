#ifndef __MIGRATION_ELEMENT_H__
#define __MIGRATION_ELEMENT_H__

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
   * The property array "taskId" of the migrations.
   */
  std::vector<Id> _taskId;
  
  /**
   * The property array "peId" (Processing Element Id) of the migrations.
   */
  std::vector<Id> _peId;

public:
  
  /**
   * @return The number of migration elements.
   */
  inline const Id count() const { return _taskId.size(); }

  /**
   * Adds a new migration element to the Migration's set.
   * @note TODO: This method must be thread-safe 
   * @param taskId The taskId which will be migrated.
   * @param peId The peId which will be migrated.
   */
  void setMigration(const Id &taskId, const Id &peId);
  
  /**
   * Get the taskId of a migration by it's index.
   * @param index The index of the queried migration.
   * @throw MIGRATION_OUT_OF_BOUNDS if tried to access a migration beyond the list limits.
   * @note This method is by design thread-unsafe when insertions are happening at the same time.
   * @return The taskId of a migration.
   */
  const Id taskId(const IndexType &index) const;

  /**
   * Get the peId of a migration by it's index.
   * @param index The index of the queried migration.
   * @throw MIGRATION_OUT_OF_BOUNDS if tried to access a migration beyond the list limits.
   * @note This method is by design thread-unsafe when insertions are happening at the same time.
   * @return The peId of a migration.  
   */  
  const Id peId(const IndexType &index) const;
};

#endif