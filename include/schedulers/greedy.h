#pragma once

#include <abstractions/scheduler.h>

#include <policies/greedy.h>

#include <concepts/pe_data.h>
#include <concepts/task_data.h>

namespace Scheduler {

/**
 * @brief Class that represents a scheduler which utilizes a greedy heuristic to output a task map.
 * @type T A concrete type that fulfills the TaskData concept.
 * @type P A concrete type that fulfills the PEData concept.
 **/
template<typename T, typename P>
class Greedy : public Abstraction::Scheduler {
public:
  using TaskData = Concepts::TaskData<T>;
  using PEData = Concepts::PEData<P>;

  Greedy() : Scheduler("greedy") {}

  /**
   * @brief The method to obtain a task map based on a greedy heuristic.
   **/
  virtual TaskMap operator()() final {
    auto ntasks = TaskData::ntasks();

    auto map = new Index[ntasks]();
    Policy::Greedy<>::map(map, ntasks, TaskData::tasks_workloads(), PEData::nPEs(), PEData::PEs_workloads());
    return map;
  }

};

}