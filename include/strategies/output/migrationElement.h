#pragma once

#include <system/traits.h>

/**
 * This class serve as a form of output to the strategies in this library.
 */
class MigrationElement {
public:
  typedef Traits<MigrationElement>::Id Id;
  typedef IMinimalParallelInputTraits::PE PE;
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

