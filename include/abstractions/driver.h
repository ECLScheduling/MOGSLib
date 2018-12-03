#pragma once

#include <system/types.h>
#include <cassert>

namespace MOGSLib {

/**
 * \brief The Initializer type is a pointer that will receive a reference for a concept, and initialize it so the scheduler can properly use it.
 */
template<typename Concept>
using Initializer = void (*)(Concept&);

/**
 * \brief The declaration of a generic data structure to represent a runtime system.
 */
template<typename Concept, RuntimeSystemEnum T>
struct Driver {
  template<RuntimeSystemEnum R>
  static void no_init(Concept&) { static_assert(R == RuntimeSystemEnum::NoRTS, "The Driver must be specialized for a given Concept and RTS.");};

  static constexpr Initializer<Concept> initializer = no_init<T>;
};

}