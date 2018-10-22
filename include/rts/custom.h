#pragma once

#include <abstractions/rts.h>

BEGIN_NAMESPACE(Abstraction)
  
/**
 * @brief The declaration of a specific data structure to represent a Custom runtime system.
 * @details This structure must contain solely static data in order to be acessed globally by Binders, Initializers, Concepts and Adaptors.
 */
template<>
struct RTS<RuntimeSystemEnum::Custom> : RTS<RuntimeSystemEnum::Custom, false> {};

END_NAMESPACE