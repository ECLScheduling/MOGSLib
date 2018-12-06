#pragma once

#include "k.h"

namespace MOGSLib { namespace Concept {

/**
 *  @class ChunksInput
 *  @brief A concept to grant access to the number of task chunks in the system.
 *  @param T A numeric type to represent the chunk amount.
 */
template<typename T>
struct ChunksInput : public K<T> {};

}}