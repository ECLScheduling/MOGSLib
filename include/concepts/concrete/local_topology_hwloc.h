#pragma once

#if USING_HWLOC

#include <hwloc.h>

#include <system/static.h>

BEGIN_NAMESPACE(Adapter)

/**
 * @brief This class implements the concept of gathering topology data through the hwloc library.
 */
class LocalTopologyHwloc {
protected:
  hwloc_topology_t topology;
  const bool cascade_delete;

public:

  /**
   * @brief Gather the topology data and create the hwloc instances to be later used.
   */
  HwlocTopology() : cascade_delete(true) {
    hwloc_topology_init(&topology);
    hwloc_topology_load(topology);
  }

  /**
   * @brief Creates an object with a pre-constructed topology and hold reference to it.
   */
  HwlocTopology(hwloc_topology_t loaded_topology) : cascade_delete(false) {
    topology = loaded_topology;
  }

  /**
   * @brief Deletes the hwloc structures if they were created inside the instance.
   */
  ~HwlocTopology() {
    if(cascade_delete)
      hwloc_topology_destroy(topology);
  }

  /**
   * @brief Gets the depth of the topology.
   */
  int depth() {
    return hwloc_topology_get_depth(topology);
  }

  /**
   * @brief Gets the amount of objects in a given depth.
   */
  int objcount_in_depth(const int &depth) {
    return hwloc_get_nbobjs_by_depth(topology, depth);
  }
};

END_NAMESPACE

#endif