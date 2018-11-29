#pragma once

#include <abstractions/rts.h>

namespace MOGSLib { namespace Abstraction {
  
/**
 * @brief The declaration of a specific data structure to represent a Custom runtime system.
 * @details This structure must contain solely static data in order to be acessed globally by Binders, Initializers, Concepts and Adaptors.
 */
template<>
struct RTS<RuntimeSystemEnum::Custom> : RTS<RuntimeSystemEnum::Custom> {};

}}