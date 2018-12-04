#pragma once

#include <system/types.h>
#include <cstdint>

namespace MOGSLib { namespace RTS {

/**
 *  @class DefaultRuntimeTraits
 *  @brief A reference structure to the types and definitions MOGSLib requires for runtime systems.
 */
template<MOGSLib::RuntimeSystemEnum T>
struct DefaultRuntimeTraits {

  /// @brief Index type used in this RTS abstraction.
  using Index = std::size_t;

  /// @brief Load type used in this RTS abstraction.
  using Load = uint_fast32_t;

  /// @brief The RTS name used to generate user-friendly messages.
  static constexpr auto name = "Unimplemented";
};

}}