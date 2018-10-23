#pragma once

#include <abstractions/driver.h>
#include <concepts/driver/chunks_input.h>

namespace MOGSLib {

template<>
inline void chunks_input_driver<RuntimeSystemEnum::OpenMP>(Concept::ChunksInput& concept) {
	concept.value = RTS::chunk_size;
}

}