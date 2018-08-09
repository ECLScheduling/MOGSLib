#pragma once

#include <abstractions/scheduler.h>
#include <policies/compact.h>

#include <concepts/abstract/pe_data.h>
#include <concepts/abstract/task_data.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename T, typename P = T>
class Compact : public Abstraction::Scheduler {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  using TaskData = Concept::TaskData<T>;
  using PEData = Concept::PEData<P>;

  Compact() : Scheduler(SchedulerTraits<MOGSLib::Abstraction::compact>::name) {}

  /**
   * @brief The method to obtain a task map based on a compact policy.
   **/
  TaskMap work() override {
    auto ntasks = TaskData::ntasks();
    auto nPEs = PEData::nPEs();

    auto map = new Index[ntasks]();
    Policy::Compact::map(map, ntasks, nPEs);
    return map;
  }

};

END_NAMESPACE