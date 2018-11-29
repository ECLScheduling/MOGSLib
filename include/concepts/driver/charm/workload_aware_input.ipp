#pragma once
#include <concepts/driver/workload_aware_input.h>
#include "workload_oblivious_input.ipp"

namespace MOGSLib {

template<>
inline void workload_aware_input_driver<RuntimeSystemEnum::Charm>(Concept::WorkloadAwareInput<>& concept) {
  Driver<Concept::WorkloadObliviousInput<RuntimeSystemEnum::Charm>, RuntimeSystemEnum::Charm>::init(concept);

  concept.pe_loads = RTS::LBDB::PU::load_prediction();
  concept.task_loads = RTS::LBDB::Chare::load_prediction();
}

}