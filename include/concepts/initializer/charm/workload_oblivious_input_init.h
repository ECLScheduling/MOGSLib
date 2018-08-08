#pragma once

#include <cassert>
#include <cstring>

#include <system/static.h>
#include <abstractions/initializer.h>

#include <rts/charm.h>

#include <concepts/concrete/workload_oblivious_input.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief Adapter structure that is responsible for initializing a WorkloadObliviousInput Adapter in the OpenMP system.
 */
template<>
struct Initializer<RuntimeSystemEnum::Charm, Adapter::WorkloadObliviousInput> {
  static constexpr auto targetRTS = RuntimeSystemEnum::Charm;
  using ConcreteAdapter = MOGSLib::Adapter::WorkloadObliviousInput;

  /**
   * @brief Reads the data gathered from OpenMP runtime to initialize the WorkloadObliviousInput concrete concept.
   * @details This implementation currently ignores Charm++ unavailable PEs and unmigrateable Chares. To fix that, check the implementation on basic_scheduler_input_init.h
   */
  static void init(ConcreteAdapter *adapter) {
    auto input = RTS<targetRTS>::stats;

    adapter->tasks = input->n_objs;
    adapter->PEs = input->nprocs();
  }
};

END_NAMESPACE