#pragma once

#include <concepts/implementation/k.h>

BEGIN_NAMESPACE(Concept)

/**
 * @brief A concrete concept to hold reference to the amount of task chunks in the system.
 */
struct ChunksInput : public K<MOGSLib::Index> {};

END_NAMESPACE