#pragma once

#include <system/types.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief The declaration of a generic data structure to represent a runtime system.
 */
template<typename Concept, RuntimeSystemEnum T>
struct Driver {
  template<RuntimeSystemEnum R>
  using Initializer = void (*)(Concept&);

  template<RuntimeSystemEnum R>
  static void no_init(Concept&) {};

  static constexpr Initializer<T> initializer = no_init<T>;
};

END_NAMESPACE
