#pragma once

#include <system/traits.h>
#include <algorithms/utility.h>

namespace EagerMap {

/**
 * @brief The struct that defines the generic EagerMap scheduler algorithms.
 *
 * @type Load A type that serve as a load abstraction to the algorithms.
 * @type UInt A type that serve as an unsigned integer to the algorithms.
 */
template<typename Load, typename UInt>
struct Algorithms {
  typename CommMatrix = int

  void generateGroups(CommMatrix comm, UInt total_elements, UInt group_elements, bool *chosen);
};

#include "eagerMapAlgorithm.ipp"

}