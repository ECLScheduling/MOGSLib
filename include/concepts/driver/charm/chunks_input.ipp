#pragma once

#include <abstractions/driver.h>
#include <concepts/driver/chunks_input.h>

namespace MOGSLib {

template<>
inline void chunks_input_driver<RuntimeSystemEnum::Charm>(Concept::ChunksInput& concept) {
  auto stats = RTS::stats;
  concept.value = stats->n_objs/stats->nprocs();
  concept.value = (concept.value == 0)? 1 : concept.value;
}

}