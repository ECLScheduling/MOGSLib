#pragma once

#include <abstractions/scheduler.h>
#include <policies/binlpt.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes the binlpt policy to output a workload-aware task map.
 **/
template<typename ... _Concepts>
class BinLPT : public Abstraction::Scheduler<Abstraction::SchedulerEnum::binlpt, _Concepts...> {
public:
  using Base = Abstraction::Scheduler<Abstraction::SchedulerEnum::binlpt, _Concepts...>;

  /**
   * @brief The method to obtain a task map based on a binlpt policy.
   **/
  TaskMap work() override {
    auto concepts = Base::concepts;
    
    auto PE_data = concepts->PE_data;
    auto task_data = concepts->task_data;
    auto chunks = *concepts->k->value;

    auto ntasks = task_data->ntasks();

    auto map = new Index[ntasks]();
    Policy::BinLPT<>::map(map, ntasks, task_data->tasks_workloads(), PE_data->nPEs(), PE_data->PEs_workloads(), chunks);
    return map;
  }

};

END_NAMESPACE