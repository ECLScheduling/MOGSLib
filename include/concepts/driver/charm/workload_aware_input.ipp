#pragma once
#include <concepts/driver/workload_aware_input.h>

#include "workload_oblivious_input.ipp"

#include <iostream>

namespace MOGSLib {

template<>
inline void workload_aware_input_driver<RuntimeSystemEnum::Charm>(Concept::WorkloadAwareInput<>& concept) {
  Driver<Concept::WorkloadObliviousInput<RuntimeSystemEnum::Charm>, RuntimeSystemEnum::Charm>::init(concept);

  auto input = RTS::stats;

  auto npes = concept.nPEs(); // only accounting the available processors. Check the driver for WorkloadObliviousInput.
  auto ntasks = concept.ntasks(); // only accounting the migrateable tasks. Check the driver for WorkloadObliviousInput.

  int *map = new int[input->nprocs()]();

  concept.pe_loads.resize(npes);
  concept.task_loads.resize(ntasks);

  // Gather the load data for the processors marked as available.
  for(decltype(npes) i = 0; i < npes; ++i) {
    auto charm_PE_id = concept.PE_ids[i];

    concept.pe_loads[i] = input->procs[charm_PE_id].bg_walltime;
    map[charm_PE_id] = i; // map the charm id to the mogslib id.
  }

  // Gather the load data for the tasks marked as migrateable.
  for(decltype(ntasks) i = 0; i < ntasks; ++i) {
    auto charm_task_id = concept.task_ids[i];
    auto pe = input->from_proc[charm_task_id];
    LDObjData &task_data = input->objData[charm_task_id];

    concept.task_loads[i] = task_data.wallTime * input->procs[map[pe]].pe_speed; // Calculate the load of a Task.
  }

  // If there are no non-migrateable tasks, we are done.
  if(ntasks == input->n_objs) {
    delete [] map;
    return;
  }

  // If there are non-migrateable tasks, we must add their workload to their host PE load.
  for(auto task = 0; task < input->n_objs; ++task) {
    LDObjData &task_data = input->objData[task];

    if(!task_data.migratable) {
      auto pe = input->from_proc[task]; // Get the PE's id where the task is allocated.
      concept.pe_loads[map[pe]] += task_data.wallTime;
    }
  }

  delete [] map;
}

}