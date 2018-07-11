#pragma once

#include <abstractions/initializer.h>
#include <cassert>

#include <mogslib/rts/charm.h>

#include <concepts/concrete/basic_scheduler_input.h>

#include <system/static.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief Adapter structure that is responsible for initializing a BasicSchedulerInput Adapter in the Charm++ system.
 */
template<>
struct Initializer<RuntimeSystemEnum::Charm, MOGSLib::Adapter::BasicSchedulerInput> {
  static constexpr auto targetRTS = RuntimeSystemEnum::Charm;
  using ConcreteAdapter = MOGSLib::Adapter::BasicSchedulerInput;
  
  /**
   * @brief Reads the data from the LBDB on Charm and pushes its data into the Adapter
   */
  static void init(ConcreteAdapter *adapter);
};

END_NAMESPACE