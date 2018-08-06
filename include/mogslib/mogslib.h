#pragma once

#include <system/traits/rts.h>
#include <system/traits/schedulers.h>

/**
 * TODO: configure.py must include necessary files into mogslib.h in order to make the correct typedefs.
 */

namespace MOGSLib {

/**
 * @brief This structure defines concrete concepts, schedulers and the other specifications such as the target system where the library will be attached to.
 * @details These definitions are generated automatically when executing scripts/configure.py with proper parameters
 */
struct Definitions {
  /**
   * TODO: This has to be generated through configure.py
   */
  static constexpr auto system = MOGSLib::Abstraction::RuntimeSystemEnum::charm;

  using RTS = MOGSLib::Abstraction::RTS<system>;

  template<typename T>
  using Initializer = MOGSLib::Abstraction::Initializer<system, T>;

  template<typename T>
  using Binder = MOGSLib::Abstraction::Binder<T>;

  /**
   * TODO: This has to be generated through configure.py
   */
  using ConcreteAdapter = MOGSLib::Adapter::WorkloadObliviousInput;
  using Scheduler = MOGSLib::Scheduler::RoundRobin<ConcreteAdapter>;
};

}