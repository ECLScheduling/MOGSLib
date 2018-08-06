#pragma once

#include <system/types.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief The declaration of a generic data structure to represent a runtime system.
 * @details A specialization to this structure must contain static data in order to be acessed globally by Binders, Initializers, Concepts and Adaptors.
 */
template<RuntimeSystemEnum T>
struct RTS {};

END_NAMESPACE