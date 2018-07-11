#pragma once

#include <abstractions/rts_representation.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief The declaration of a specific data structure to represent the Charm++ runtime system.
 * @details This structure must contain solely static data in order to be acessed globally by Binders, Initializers, Concepts and Adaptors.
 */
template<>
struct RTS<RuntimeSystemEnum::Charm> {
  static constexpr auto SystemVal = RuntimeSystemEnum::Charm;
  
  // This inquires that these names have to be declared before including this header into the source file.
  using LDStats = BaseLB::LDStats*;
  
  static LDStats stats;
};

END_NAMESPACE

BEGIN_NAMESPACE(RTS)
using Charm = MOGSLib::Abstraction::RTS<MOGSLib::Abstraction::RuntimeSystemEnum::Charm>;
END_NAMESPACE