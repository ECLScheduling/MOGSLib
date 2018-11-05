#pragma once
#include <concepts/driver/workload_oblivious_input.h>

namespace MOGSLib {

template<>
inline void workload_oblivious_input_driver<RuntimeSystemEnum::Charm>(Concept::WorkloadObliviousInput<RuntimeSystemEnum::Charm>& concept) {
  auto input = RTS::stats;

  auto nPEs = input->nprocs();
  auto ntasks = input->n_objs;

  concept.PE_ids.resize(nPEs);
  concept.task_ids.resize(ntasks);

  // Count only the available processors.
  Index i = 0;
  for(auto pe = 0; pe < nPEs; ++pe)
    if(input->procs[pe].available)
      concept.PE_ids[i++] = pe;

  // Count only the migrateable tasks.
  i = 0;
  for(auto task = 0; task < ntasks; ++task)
    if(input->objData[task].migratable)
      concept.task_ids[i++] = task;
}

}