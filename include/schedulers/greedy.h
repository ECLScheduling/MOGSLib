#pragma once

#include <abstractions/scheduler.h>
#include <policies/greedy.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes a greedy heuristic to output a task map.
 **/
template<typename ... _Concepts>
class Greedy : public Abstraction::Scheduler<MOGSLib::SchedulerEnum::greedy, _Concepts...> {
public:
  using Base = Abstraction::Scheduler<MOGSLib::SchedulerEnum::greedy, _Concepts...>;

  /**
   * @brief The method to obtain a task map based on a greedy heuristic.
   **/
  TaskMap work() override {
    auto concepts = Base::concepts;

    auto ntasks = concepts->task_data->ntasks();
    auto map = new Index[ntasks]();
    
    Policy::Greedy<>::map(map, ntasks, concepts->task_data->tasks_workloads(), concepts->PE_data->nPEs(), concepts->PE_data->PEs_workloads());
    return map;
  }
};

END_NAMESPACE
