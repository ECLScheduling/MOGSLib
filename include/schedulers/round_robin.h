#pragma once

#include <abstractions/scheduler.h>

#include <policies/round_robin.h>

#include <concepts/abstract/pe_data.h>
#include <concepts/abstract/task_data.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes a round robin heuristic to output a task map.
 **/
template<typename T, typename P = T>
class RoundRobin : public Abstraction::Scheduler {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  using TaskData = Concept::TaskData<T>;
  using PEData = Concept::PEData<P>;

  RoundRobin() : Scheduler(SchedulerTraits<MOGSLib::Abstraction::round_robin>::name) {}

  /**
   * @brief The method to obtain a task map based on a roundrobin heuristic.
   **/
  TaskMap work() override {
    auto ntasks = TaskData::ntasks();
    auto nPEs = PEData::nPEs();

    auto map = new Index[ntasks]();
    Policy::RoundRobin::map(map, ntasks, nPEs);
    return map;
  }

};

END_NAMESPACE