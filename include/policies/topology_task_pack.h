#pragma once

#include <system/type_definitions.h>
#include <system/static.h>

#include <vector>

BEGIN_NAMESPACE(Policy)

/**
 * @brief A workload-unaware policy that iterativelly assigns a task to a PE based on their id.
 * @details This policy aggregates adjacent tasks into task packs that are assigned to the same PE.
 */
template<typename LocalTopology>
class TopologyPack {
protected:

  static Index current_PE = 0;

public:

  static void shared_level(const LocalTopology &local_topology, const Index &level, const Index &begin, const Index &end, TaskMap &map) {
    auto objects = local_topology.objcount_in_depth(level);
    auto segment_size = end-begin;
    auto left_over = segment_size%objects;

    if(level+1 >= local_topology.depth()){
      for(Index i = begin; i < end; ++i)
        map[i] = current_PE;
      ++current_PE;
      return;
    }
    
    auto first_pack_end = begin + segment_size + left_over;

    shared_level(local_topology, level+1, begin, first_pack_end);
    for(Index i = 1; i < objects; ++i)
      shared_level(local_topology, level+1, first_pack_end+(segment_size*(i-1)), first_pack_end+segment_size*i);
  }

  static void map(TaskMap &map, const Index &ntasks, const LocalTopology &local_topology) {
    current_PE = 0;
    compute_shared_level(local_topology, 0, 0, ntasks, map);
  }
};

END_NAMESPACE