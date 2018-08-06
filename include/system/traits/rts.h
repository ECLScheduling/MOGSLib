#pragma once

#include <system/types.h>

namespace MOGSLib {

/**
 * @brief This structure holds reference to datatypes and useful information about a specific RTS.
 * @details The only required traits in these structures are Index and Load which are used in the majority of schedulers and concepts.
 */
template<Abstractions::RuntimeSystemEnum T>
struct RuntimeTraits {

  /**
   * @brief The type definition that will serve as index in MOGSLib.
   */
  using Index = std::size_t;

  /**
   * @brief The type definition that will serve to quantify load values in MOGSLib.
   */
  using Load = uint_fast32_t;

};

template<>
struct RuntimeTraits<Abstractions::RuntimeSystemEnum::charm> {
  /**
   * @brief The type definition that will serve as index in MOGSLib when used in Charm++.
   */
  using Index = std::size_t;

  /**
   * @brief The type definition that will serve to quantify load values in MOGSLib when used in Charm++.
   */
  using Load = double;
};

template<>
struct RuntimeTraits<Abstractions::RuntimeSystemEnum::openmp> {
  /**
   * @brief The type definition that will serve as index in MOGSLib when used in OpenMP.
   */
  using Index = unsigned int;

  /**
   * @brief The type definition that will serve to quantify load values in MOGSLib when used in OpenMP.
   */
  using Load = unsigned int;

};

}