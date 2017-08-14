#pragma once

#include <system/traits.h>

#include <structures/simplePE.h> //TODO: This include must be uneeded in future versions.
#include <structures/simpleTask.h> //TODO: This include must be uneeded in future versions.

/**
 * This class serve as a form of output to the strategies in this library.
 */
class MigrationElement {
public:
  typedef Traits<MigrationElement>::Id Id;
  typedef DefaultInputTraits::PE PE;
  typedef std::vector<Id>::size_type IndexType;
  
public:
  /**
   * A vector of PEs with their loads adjusted.
   */
  std::vector<PE*> mappedPEs;

  /**
   * Sets an PE as an output mapping.
   */
  void set(PE *aPE) {
    mappedPEs.push_back(aPE);
  }

};

