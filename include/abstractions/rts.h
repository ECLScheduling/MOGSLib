#pragma once

#include <system/traits/rts.h>

namespace MOGSLib { namespace Abstraction {

/**
 * @brief The declaration of a generic data structure to represent a runtime system.
 * @details Specialized structures to represent runtime systems must be given in the form of template specialization that inherit from this structure.
 * @type T The enumerate value for the RTS.
 * @type Spec A boolean value to denote if the RTS type is a specialization. It is implicitly set to true to improve user code readability.
 *
 * @error Calling a template specialization that does not exist is unintended and will yield a compile-time error.
 */
template<RuntimeSystemEnum T, bool Spec = true>
struct RTS {
	static constexpr auto id = T;
  	static constexpr auto name = RuntimeTraits<T>::name;

	static_assert(!(Spec && T != RuntimeSystemEnum::NoRTS), "The RTS structure must be specialized for the runtime system.");
};

}}
