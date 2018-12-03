#pragma once

#include <abstractions/scheduler.h>
#include <policies/compact.h>

namespace MOGSLib { namespace Scheduler {

/**
 * \brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename ... _Concepts>
class Compact : public Abstraction::Scheduler<MOGSLib::SchedulerEnum::compact, _Concepts...> {
public:
  using Base = Abstraction::Scheduler<MOGSLib::SchedulerEnum::compact, _Concepts...>;

  /**
   * \brief The method to obtain a task map based on a compact policy.
   **/
  TaskMap work() override {
    auto concepts = Base::concepts;
    
    auto ntasks = concepts->task_data->ntasks();
    auto nPEs = concepts->PE_data->nPEs();

    auto map = new Index[ntasks]();
    Policy::Compact::map(map, ntasks, nPEs);
    return map;
  }

};

}}