#pragma once

#include "naiveBasicInput.h"

/**
 * A concrete BasicInput class that also offers the starting load capability information.
 */
class NaiveBasicInputInitialLoad : public BasicInputTaskContainer, public WithStartingLoad {
protected:

  /**
   * A map linking a PEs id to a load.
   */
  const LoadMap _PEs;

  /**
   * A set of Ids that corresponds to the PEs.
   */
  const SetOfId _PEsIds;

public:

  /**
   * Constructor for the class that initializes all data. 
   */
  NaiveBasicInputInitialLoad(const SetOfId &tasks, const LoadMap &PEs) : BasicInputTaskContainer(tasks), _PEs(PEs), _PEsIds(getAllKeysFromLoadMap(PEs)) {}

  virtual ~NaiveBasicInputInitialLoad() {}

  /**
   * @return All the PEs Ids.
   */
  const SetOfId &getPEs() const;

  /**
   * Method to get an initial PE Load.
   * @param peId The id of the PE in the system.
   * @return The Load of the PE.
   */
  const Load& getPELoad(const Id &PEId) const;

protected:
  
  /**
   * Extracts all the keys (Ids) from a Loadmap. This method is used to initialize the set of PEids.
   */
  const SetOfId getAllKeysFromLoadMap(const LoadMap &loadMap) const;
};