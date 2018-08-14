#pragma once

#include <hwloc.h>

#include <system/static.h>

BEGIN_NAMESPACE(Concept)

/**
 * @brief This class implements the concept of gathering topology data through the hwloc library.
 */
class LocalTopologyHwloc : public Abstraction::Concept {
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

  /**
   * @brief A function to initialize all the concepts values and references to be used by the scheduler.
   * @details The init method will be called by MOGSLib before invoking the scheduler and after all the RTS data is set-up.
   */
  template<MOGSLib::Abstraction::RuntimeSystemEnum T>
  void init() {}
};

END_NAMESPACE