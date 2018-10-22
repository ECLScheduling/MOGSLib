#pragma once

#include <abstractions/driver.h>
#include <concepts/implementation/chunks_input.h>

namespace MOGSLib {

template<RuntimeSystemEnum T>
inline void chunks_input_driver(Concept::ChunksInput& concept) { static_assert(T == RuntimeSystemEnum::NoRTS, "Uninmplemented Driver for the ChunksInput concept within the designated RTS."); }

template<RuntimeSystemEnum T>
struct Driver<Concept::ChunksInput, T> {
  static constexpr Initializer<Concept::ChunksInput> init = chunks_input_driver<T>;
};

}