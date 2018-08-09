#pragma once

#include <abstractions/scheduler.h>

#include <policies/task_pack.h>

#include <concepts/abstract/pe_data.h>
#include <concepts/abstract/task_data.h>
#include <concepts/abstract/k_data.h>

#include <system/static.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename T, typename P = T, typename K = T>
class TaskPack : public Abstraction::Scheduler {
public:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  using TaskData = Concept::TaskData<T>;
  using PEData = Concept::PEData<P>;
  using KData = Concept::KData<P>;

  TaskPack() : Scheduler(SchedulerTraits<MOGSLib::Abstraction::task_pack>::name) {}

  /**
   * @brief The method to obtain a task map based on a compact policy.
   **/
  TaskMap work() override {
    auto ntasks = TaskData::ntasks();
    auto nPEs = PEData::nPEs();
    auto npacks = KData::k();

    auto map = new Index[ntasks]();
    Policy::TaskPack::map(map, ntasks, nPEs, npacks);
    return map;
  }

};

END_NAMESPACE