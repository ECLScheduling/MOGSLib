#pragma once

#include <abstractions/scheduler.h>

#include <policies/greedy.h>

#include <concepts/abstract/pe_data.h>
#include <concepts/abstract/task_data.h>

#include <system/static.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes a greedy heuristic to output a task map.
 * @type T A concrete type that fulfills the TaskData concept.
 * @type P A concrete type that fulfills the PEData concept.
 **/
template<typename T, typename P = T>
class Greedy : public Abstraction::Scheduler {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;
  using Load = MOGSLib::Load;

  using TaskData = MOGSLib::Concept::TaskData<T>;
  using PEData = MOGSLib::Concept::PEData<P>;

  Greedy() : Scheduler(SchedulerTraits<MOGSLib::Abstraction::greedy>::name) {}

  /**
   * @brief The method to obtain a task map based on a greedy heuristic.
   **/
  TaskMap work() override {
    auto ntasks = TaskData::ntasks();

    auto map = new Index[ntasks]();
    Policy::Greedy<>::map(map, ntasks, TaskData::tasks_workloads(), PEData::nPEs(), PEData::PEs_workloads());
    return map;
  }
};

END_NAMESPACE