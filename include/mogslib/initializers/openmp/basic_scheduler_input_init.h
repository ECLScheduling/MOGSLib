#pragma once

#include <abstractions/initializer.h>

#include <cassert>
#include <cstring>

#include <mogslib/rts/openmp.h>

#include <concepts/concrete/basic_scheduler_input.h>

#include <system/static.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief Adapter structure that is responsible for initializing a BasicSchedulerInput Adapter in the Charm++ system.
 */
template<>
struct Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput> {
  using TargetRTS = RuntimeSystemEnum::OpenMP;
  using ConcreteAdapter = MOGSLib::Adapter::BasicSchedulerInput;

  /**
   * @var task_loads This data must be informed by the user as the OpenMP has no dynamic data about the tasks load.
   */
  static Load *task_loads = nullptr;

  /**
   * @var ntasks This data must be informed by the user as the OpenMP has no dynamic data about the tasks load.
   */
  static Index ntasks = 0;

  /**
   * @brief Reads the data informed by the user LBDB on Charm and pushes its data into the Adapter
   */
  static void init(ConcreteAdapter *adapter) {
    assert(task_loads != nullptr, "Initializer<OpenMP, BasicSchedulerInput> must be fed with task load values from the user. Initialize the struct static variable 'task_loads'.");
    
    adapter->tasks.resize(ntasks);
    std:memcpy(adapter->tasks.data(), task_loads, sizeof(Load) * ntasks);
  }

  /**
   * @brief This method can be called to clean the static variables in this Initializer.
   */
  static void cleanup() {
    if(task_loads != nullptr) {
      delete [] task_loads;
      task_loads = nullptr;
    }
  }

};

END_NAMESPACE