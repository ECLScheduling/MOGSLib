#pragma once

#include <system/type_definitions.h>
#include <abstractions/input.h>

namespace MOGSLib { namespace Scheduler {

/**
 * \brief This structure serve as a concept to be implemented by structures that will provide the most basic input for data-parallel schedulers.
 */
template<>
struct Input<MOGSLib::InputType::simple> {
  using Index = MOGSLib::Index;
  
  /**
   * \brief Gets the amount of tasks in a scheduler input.
   */
  virtual Index ntasks() = 0;

  /**
   * \brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  virtual Index ntasks() const = 0;

  /**
   * \brief Gets the amount of PUs in a scheduler input.
   */
  virtual Index npus() = 0;

  /**
   * \brief Gets the amount of PUs in a scheduler input.
   * @details This method has a const specifier.
   */
  virtual Index npus() const = 0;
};

}}