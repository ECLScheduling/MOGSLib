#pragma once

#include <lb/input/basicInput.h>

/**
 * A concrete BasicInput class that also offers the starting load capability information.
 */
class StartingLoadAwareBasicInput : public BasicInput, public WithStartingLoad {
public:
  typedef Traits<BasicInput>::LoadMap LoadMap;

protected:

  /**
   * A map linking a PEs id to a load.
   */
  const LoadMap _PEs;

  /**
   * Constructor for the class that initializes all data. 
   */
  StartingLoadAwareBasicInput(const LoadMap &PEs, const LoadMap &tasks ) :  _PEs(PEs), _tasks(tasks) {}

  /**
   * @return All the PEs Ids.
   */
  const SetOfId &getPEsIds() const;
};