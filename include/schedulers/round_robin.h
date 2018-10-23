#pragma once

#include <abstractions/scheduler.h>
#include <policies/round_robin.h>

namespace MOGSLib { namespace Scheduler {

/**
 * @brief Class that represents a scheduler which utilizes a round robin heuristic to output a task map.
 **/
template<typename ... _Concepts>
class RoundRobin : public Abstraction::Scheduler<MOGSLib::SchedulerEnum::round_robin, _Concepts...> {
public:
  using Base = Abstraction::Scheduler<MOGSLib::SchedulerEnum::round_robin, _Concepts...>;

  /**
   * @brief The method to obtain a task map based on a roundrobin heuristic.
   **/
  TaskMap work() override {
    auto concepts = Base::concepts;
    
    auto ntasks = concepts->task_data->ntasks();
    auto nPEs = concepts->PE_data->nPEs();

    auto map = new Index[ntasks]();
    Policy::RoundRobin::map(map, ntasks, nPEs);
    return map;
  }

};

}}