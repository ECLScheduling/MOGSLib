#pragma once

#include <abstractions/driver.h>
#include <concepts/implementation/workload_aware_input.h>

namespace MOGSLib {

template<RuntimeSystemEnum T>
inline void workload_aware_input_driver(Concept::WorkloadAwareInput& concept) { static_assert(T == RuntimeSystemEnum::NoRTS, "Uninmplemented Driver for the WorkloadAwareInput concept within the designated RTS."); }

template<RuntimeSystemEnum T>
struct Driver<Concept::WorkloadAwareInput, T> {
  static constexpr Initializer<Concept::WorkloadAwareInput> init = workload_aware_input_driver<T>;
};

}