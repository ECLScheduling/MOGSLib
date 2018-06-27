#pragma once

#ifdef LINKED_TO_CHARM

#include <abstractions/rts_representation.h>

// Charm++ specific includes.
#include <ckgraph.h>
#include <CentralLB.h>

namespace MOGSLib {

/**
 * @brief The declaration of a specific data structure to represent the Charm++ runtime system.
 * @details This structure must contain solely static data in order to be acessed globally by Binders, Initializers, Concepts and Adaptors.
 */
template<>
struct RTS<RuntimeSystemEnum::Charm> {
  using LDStats = BaseLB::LDStats;
  
  static LDStats *stats;
};

}

#endif