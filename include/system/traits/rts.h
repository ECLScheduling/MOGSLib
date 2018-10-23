#pragma once

#include <system/types.h>
#include <cstdint>

namespace MOGSLib {

/**
 * @brief This structure holds reference to datatypes and useful information about a specific RTS.
 * @details The only required traits in these structures are Index and Load which are used in the majority of schedulers and concepts.
 */
template<RuntimeSystemEnum T>
struct RuntimeTraits {

  /**
   * @brief The type definition that will serve as index in MOGSLib.
   */
  using Index = std::size_t;

  /**
   * @brief The type definition that will serve to quantify load values in MOGSLib.
   */
  using Load = uint_fast32_t;

  static constexpr auto name = "Unimplemented";
};

template<>
struct RuntimeTraits<RuntimeSystemEnum::Charm> {
  /**
   * @brief The type definition that will serve as index in MOGSLib when used in Charm++.
   */
  using Index = std::size_t;

  /**
   * @brief The type definition that will serve to quantify load values in MOGSLib when used in Charm++.
   */
  using Load = double;

  /**
   * @brief The name of the system so it can be referenced on user-friendly messages.
   */
  static constexpr auto name = "Charm++";
};

template<>
struct RuntimeTraits<RuntimeSystemEnum::OpenMP> {
  /**
   * @brief The type definition that will serve as index in MOGSLib when used in OpenMP.
   */
  using Index = unsigned int;

  /**
   * @brief The type definition that will serve to quantify load values in MOGSLib when used in OpenMP.
   */
  using Load = unsigned int;

  /**
   * @brief The name of the system so it can be referenced on user-friendly messages.
   */
  static constexpr auto name = "OpenMP";

};

}