#pragma once

#include "dependencies/base.h"

namespace MOGSLib { namespace Policy {

template<typename ... Deps>
class TaskPack;

/**
 *  @class TaskPack
 *  @tparam Id An index type to organize PUs and tasks.
 *  @brief A workload-unaware policy that iterativelly assigns a task to a PU based on their id.
 *  @details This policy aggregates adjacent tasks into task packs that are assigned to the same PE.
 */
template<typename I>
struct TaskPack<MOGSLib::Dependency::Base<I>> {
  using Deps = MOGSLib::Dependency::Base<I>;
  using Id = typename Deps::Id;
  using Schedule = typename Deps::Schedule;

  /**
   *  @brief Divide the tasks into packs and assign them to PUs in increasing index.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   *  @param npacks The amount of packs to create.
   */
  static void map(Schedule &map, const Id &ntasks, const Id &npus, const Id &npacks) {
    const auto pack_size = ntasks/npacks;
    const auto left_over = ntasks%npacks;

    for(Id i = 0; i < left_over; ++i)
      map[i] = 0;

    for(Id i = 0; i < npacks; ++i)
      for(Id j = 0; j < pack_size; ++j)
        map[i*pack_size + j + left_over] = i%npus;
  }
};

}}