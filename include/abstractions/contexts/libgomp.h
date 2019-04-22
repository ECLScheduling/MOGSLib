#pragma once

#include <abstractions/structures/input/workload_aware.h>

#include <abstractions/rts/openmp/openmp.h>
#include <omp.h>

namespace MOGSLib { namespace Context {

/**
 * @class LibGOMP
 * @brief The necessary definitions and functions to perform workload aware load balancing through MOGSLib in the context of LibGOMP.
 */
template<typename I, typename L>
struct LibGOMP {
  using Id = I;
  using Load = L;
  using SchedulerInput = MOGSLib::Input::WorkloadAware<Id, Load>;

  SchedulerInput _input;

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