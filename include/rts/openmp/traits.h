#pragma once

#include <system/traits/rts.h>

namespace MOGSLib { namespace RTS {

/**
 *  @class OpenMPBaseTraits
 *  @brief The expression of OpenMP minimum traits required by MOGSLib.
 */
struct OpenMPBaseTraits {
  /// @brief The type definition that will serve as index in MOGSLib when used in OpenMP.
  using Index = std::size_t;

  /// @brief The type definition that will serve to quantify load values in MOGSLib when used in OpenMP.
  using Load = std::size_t;

  /// @brief The name of the system so it can be referenced on user-friendly messages.
  static constexpr auto name = "OpenMP";
};

/**
 *  @class DefaultRuntimeTraits_OpenMP
 *  @brief A structure to express additional traits required by functionalities in MOGSLib over the OpenMP API.
 */
template<>
struct DefaultRuntimeTraits<MOGSLib::RuntimeSystemEnum::OpenMP> : public OpenMPBaseTraits {};

}}