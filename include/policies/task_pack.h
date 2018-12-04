#pragma once

namespace MOGSLib { namespace Policy {

/**
 *  @class TaskPack
 *  @brief A workload-unaware policy that iterativelly assigns a task to a PU based on their id.
 *  @details This policy aggregates adjacent tasks into task packs that are assigned to the same PE.
 */
class TaskPack {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  /**
   *  @brief Divide the tasks into packs and assign them to PUs in increasing index.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   *  @param npacks The amount of packs to create.
   */
  static void map(TaskMap &map, const Index &ntasks, const Index &npus, const Index &npacks) {
    auto pack_size = ntasks/npacks;
    auto left_over = ntasks%npacks;

    for(decltype(left_over) i = 0; i < left_over; ++i)
      map[i] = 0;

    for(decltype(npacks) i = 0; i < npacks; ++i)
      for(decltype(pack_size) j = 0; j < pack_size; ++j)
        map[i*pack_size + j + left_over] = i%npus;
  }
};

}}