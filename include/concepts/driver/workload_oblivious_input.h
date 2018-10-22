#pragma once

#include <abstractions/driver.h>
#include <concepts/implementation/workload_oblivious_input.h>

namespace MOGSLib {

template<RuntimeSystemEnum T>
inline void workload_oblivious_input_driver(Concept::WorkloadObliviousInput& concept) { static_assert(T == RuntimeSystemEnum::NoRTS, "Uninmplemented Driver for the WorkloadObliviousInput concept within the designated RTS."); }

template<RuntimeSystemEnum T>
struct Driver<Concept::WorkloadObliviousInput, T> {
  static constexpr Initializer<Concept::WorkloadObliviousInput> init = workload_oblivious_input_driver<T>;
};

}