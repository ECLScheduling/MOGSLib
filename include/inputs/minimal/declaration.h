#pragma once

#include <abstractions/input.h>

namespace MOGSLib { namespace Input {

/**
 *  @class Declaration_Minimal
 *  @brief This structure declares the interface for most basic input structure for MOGSLib schedulers.
 *  @tparam I The index data type definition.
 */
template<typename I>
struct Declaration<MOGSLib::InputEnum::minimal, I> {
  using Index = I;
  
  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   */
  virtual Index ntasks() = 0;

  /**
   *  @brief Gets the amount of tasks in a scheduler input.
   *  @details This method has a const specifier.
   */
  virtual Index ntasks() const = 0;

  /**
   *  @brief Gets the amount of PUs in a scheduler input.
   */
  virtual Index npus() = 0;

  /**
   *  @brief Gets the amount of PUs in a scheduler input.
   *  @details This method has a const specifier.
   */
  virtual Index npus() const = 0;
};

}}