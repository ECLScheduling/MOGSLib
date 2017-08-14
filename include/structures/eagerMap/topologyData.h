#pragma once

#include <system/traits.h>
#include "hardwareElement.h"

namespace EagerMap {

/**
 * Struct that wraps the information about the topology that is used in the EagerMap strategy.
 */
struct TopologyData {
public:
  typedef EagerMapTraits::UInt UInt;

  /**
   * The total ammount of levels in the hardware hierarchy.
   */
  const UInt nLevels;

  /**
   * The array of number of hardware elements for each topology level. It's size is nLevels.
   * @details The index 0 is not used as it represent the tasks of the application, the first index represents the ammount of PEs that the topology have, each subsequent index of the array accounts for an outter shared level such as caches or interconnections.
   */
  const UInt * const elementsInLevel;

  /**
   * The root hardware element node.
   */
  const HardwareElement *rootNode;

  /**
   * The constructor for the EagerMapTopologyData which initialized the internal state.
   * @param nSharedLevels The ammount of shared levels in the hardware topology, this number will be incremented by 1 to calculate the nLevels. The added level represents the environment's PEs.
   * @param nElementsLevel The array that contains the information about how many hardware elements there are inside each level of the hardware topology. It's size must be nSharedLevels+2 and the first value is assumed to be 0.
   * @param rootNode The root hardware element node of the physical topology.
   */
  TopologyData(const UInt nSharedLevels, const UInt * const nElementsLevel, const HardwareElement *aRootNode) : nLevels(nSharedLevels+1), elementsInLevel(nElementsLevel), rootNode(aRootNode) {}

  virtual ~TopologyData() {
    delete rootNode;
  }

  /**
   * @return The ammount of resources, which is the sum of elements in each level of the topology.
   */
  const UInt elementsSum() const {
    UInt sum = 0;
    for(UInt i = 0; i < nLevels; ++i)
      sum += elementsInLevel[i];
    return sum;
  }

};

}