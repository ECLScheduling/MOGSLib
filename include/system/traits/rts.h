#pragma once

#include <system/types.h>
#include <cstdint>

namespace MOGSLib { namespace RTS {

/**
 * \brief This structure holds reference to datatypes and useful information about the specificities of a RTS.
 * @details This structure holds reference to the global definitions any RTS must have. Additional requirements fore each system are exposed in their own file at include/rts/RTSNAME/traits.ipp
 */
template<MOGSLib::RuntimeSystemEnum T>
struct DefaultRuntimeTraits {

  /**
   * \brief The type definition that will serve as index in MOGSLib.
   */
  using Index = std::size_t;

  /**
   * \brief The type definition that will serve to quantify load values in MOGSLib.
   */
  using Load = uint_fast32_t;

  /**
   * \brief The name of the system so it can be referenced on user-friendly messages.
   */
  static constexpr auto name = "Unimplemented";
};

}}