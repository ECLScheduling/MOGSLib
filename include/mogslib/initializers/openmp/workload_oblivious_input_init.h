#pragma once

#include <abstractions/initializer.h>

#include <cassert>
#include <cstring>

#include <mogslib/rts/openmp.h>

#include <concepts/concrete/workload_oblivious_input.h>

#include <system/static.h>

#include <iostream>

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

    std::cout << "WorkloadObliviousInput init with " << RTS<targetRTS>::ntasks << " tasks and " << RTS<targetRTS>::nPEs << " PEs." << std::endl;
  }
};

END_NAMESPACE