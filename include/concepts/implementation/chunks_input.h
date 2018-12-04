#pragma once

#include "k.h"

namespace MOGSLib { namespace Concept {

/**
 *  @class ChunksInput
 *  @brief A concept to grant access to the number of task chunks in the system.
 */
struct ChunksInput : public K<MOGSLib::Index> {};

}}