#pragma once

#include <abstractions/structures/input/workload_aware.h>
#include <model/policies/dependencies/base.h>

#include <abstractions/rts/openmp/openmp.h>

namespace MOGSLib { namespace Context {

/**
 * @class LibGOMP
 * @brief The necessary definitions and functions to perform workload aware load balancing through MOGSLib in the context of LibGOMP.
 */
struct LibGOMP {
  using Id = Traits::Id;
  using Load = Traits::Load;
  using SchedulerInput = MOGSLib::Input::WorkloadAware<Id, Load>;
  using Schedule = typename MOGSLib::Dependency::Base<Id>::Schedule;
  
  SchedulerInput _input;

  Schedule _schedule;

  inline Id* scheduleRaw() {
    return _schedule.data();
  }

  inline Schedule& schedule() {
    _schedule.resize(_input.ntasks());
    return _schedule;
  }

  /**
   * @brief An auxiliar method to set the input loads for the input structure used by the scheduler.
   * @param loads The vector of loads.
   */
  inline void set_loads(std::vector<Load> &loads) {
    MOGSLib::RTS::OpenMP::set_iteration_count(loads.size());
    _input.tasks = loads;
  }

  /**
   * @brief A required method for workload aware schedulers to obtain the workload input data.
   * @return The workload input structure to be used by the scheduler.
   */
  inline auto& input() {
    _input.pus.resize(MOGSLib::RTS::OpenMP::threads);
    for(Id i = 0; i < _input.pus.size(); ++i)
      _input.pus[i] = 0;
    return _input;
  }

  /**
   * @brief Obtains the chunk count defined by the OpenMP runtime.
   */
  inline auto nchunks() { return MOGSLib::RTS::OpenMP::chunks;  }
};

}}