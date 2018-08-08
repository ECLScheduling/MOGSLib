#pragma once

#include <cassert>
#include <cstring>

#include <system/static.h>
#include <abstractions/initializer.h>

#include <rts/openmp.h>

#include <concepts/concrete/workload_oblivious_input.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief Adapter structure that is responsible for initializing a WorkloadObliviousInput Adapter in the OpenMP system.
 */
template<>
struct Initializer<RuntimeSystemEnum::OpenMP, Adapter::WorkloadObliviousInput> {
  static constexpr auto targetRTS = RuntimeSystemEnum::OpenMP;
  using ConcreteAdapter = MOGSLib::Adapter::WorkloadObliviousInput;

  /**
   * @brief Reads the data gathered from OpenMP runtime to initialize the WorkloadObliviousInput concrete concept.
   */
  static void init(ConcreteAdapter *adapter) {
    adapter->tasks = RTS<targetRTS>::ntasks;
    adapter->PEs = RTS<targetRTS>::nPEs;
  }
};

END_NAMESPACE