#pragma once
#include <concepts/driver/workload_oblivious_input.h>

namespace MOGSLib {

template<>
inline void workload_oblivious_input_driver<RuntimeSystemEnum::Charm>(Concept::WorkloadObliviousInput<RuntimeSystemEnum::Charm>& concept) {
  auto nPEs = RTS::LBDB::PU::count();
  auto ntasks = RTS::LBDB::Chare::count();
}

}