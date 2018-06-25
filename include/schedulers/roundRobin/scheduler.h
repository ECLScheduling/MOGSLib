#pragma once

#include <abstractions/scheduler.h>

#include <policies/roundRobin/policy.h>

#include <concepts/pe_data.h>
#include <concepts/task_data.h>

namespace Scheduler {

/**
 * @brief Class that represents a scheduler which utilizes a round robin heuristic to output a task map.
 **/
template<typename T, typename P>
class RoundRobin : public Abstraction::Scheduler {
public:
  using TaskData = Concepts::TaskData<T>;
  using PEData = Concepts::PEData<T>;

  RoundRobin() : Scheduler("roundrobin") {}

  /**
   * @brief The method to obtain a task map based on a roundrobin heuristic.
   **/
  virtual TaskMap operator()() final {
    auto ntasks = TaskData::ntasks();
    auto nPEs = PEData::nPEs();

    auto map = new Index[ntasks]();
    Policy::RoundRobin::map(map, ntasks, nPEs);
    return map;
  }

};

}