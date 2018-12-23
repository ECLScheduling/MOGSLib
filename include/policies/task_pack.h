#pragma once

#include <system/traits.h>

namespace MOGSLib { namespace Policy {

/**
 *  @class TaskPack
 *  @tparam Id An index type to organize PUs and tasks.
 *  @brief A workload-unaware policy that iterativelly assigns a task to a PU based on their id.
 *  @details This policy aggregates adjacent tasks into task packs that are assigned to the same PE.
 */
template<typename Id>
class TaskPack {
public:
  using Index = Id;
  using Schedule = typename MOGSLib::Traits::Policy<Id>::Output;

  /**
   *  @brief Divide the tasks into packs and assign them to PUs in increasing index.
   *  @param map The map of task-to-pu that will serve as the output.
   *  @param ntasks The amount of tasks to be scheduled.
   *  @param npus The amount of pus to be scheduled.
   *  @param npacks The amount of packs to create.
   */
  static void map(Schedule &map, const Index &ntasks, const Index &npus, const Index &npacks) {
    const auto pack_size = ntasks/npacks;
    const auto left_over = ntasks%npacks;

    for(Index i = 0; i < left_over; ++i)
      map[i] = 0;

    for(Index i = 0; i < npacks; ++i)
      for(Index j = 0; j < pack_size; ++j)
        map[i*pack_size + j + left_over] = i%npus;
  }
};

}}