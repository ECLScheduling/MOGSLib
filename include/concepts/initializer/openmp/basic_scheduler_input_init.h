#pragma once

#include <cassert>
#include <cstring>

#include <system/static.h>
#include <abstractions/initializer.h>

#include <rts/openmp.h>

#include <concepts/concrete/basic_scheduler_input.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief Adapter structure that is responsible for initializing a BasicSchedulerInput Adapter in the OpenMP system.
 */
template<>
struct Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput> {
  static constexpr auto targetRTS = RuntimeSystemEnum::OpenMP;
  using ConcreteAdapter = MOGSLib::Adapter::BasicSchedulerInput;

  /**
   * @brief Reads the data gathered from OpenMP runtime to initialize the BasicSchedulerInput concrete concept.
   * @details This method currently only works for strategies that are not workload aware. 
   */
  static void init(ConcreteAdapter *adapter);
};

END_NAMESPACE