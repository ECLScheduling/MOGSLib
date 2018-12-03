#pragma once

#include <system/traits/rts.h>

namespace MOGSLib {

template<>
struct DefaultRuntimeTraits<RuntimeSystemEnum::OpenMP> {
  /**
   * \brief The type definition that will serve as index in MOGSLib when used in OpenMP.
   */
  using Index = std::size_t;

  /**
   * \brief The type definition that will serve to quantify load values in MOGSLib when used in OpenMP.
   */
  using Load = std::size_t;

  /**
   * \brief The name of the system so it can be referenced on user-friendly messages.
   */
  static constexpr auto name = "OpenMP";
};

}