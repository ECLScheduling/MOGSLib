#pragma once

#include <abstractions/scheduler.h>

#include <policies/task_pack.h>

#include <concepts/pe_data.h>
#include <concepts/task_data.h>

#include <system/static.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename T, typename P = T>
class TaskPack : public Abstraction::Scheduler {
public:
  static constexpr auto TypeToken = MOGSLib::SchedulerTypes::TaskPack;

  using TaskData = Concept::TaskData<T>;
  using PEData = Concept::PEData<P>;

  RoundRobin() : Scheduler(SchedulerTraits<TypeToken>::name) {}

  /**
   * @brief The method to obtain a task map based on a compact policy.
   **/
  TaskMap work() override {
    auto ntasks = TaskData::ntasks();
    auto nPEs = PEData::nPEs();

    auto map = new Index[ntasks]();
    Policy::TaskPack::map(map, ntasks, nPEs);
    return map;
  }

};

END_NAMESPACE