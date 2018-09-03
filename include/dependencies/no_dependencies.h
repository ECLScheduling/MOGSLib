#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Dependency)

/**
 * @brief Empty dependency class for a fully autonomous scheduler.
 * @details If you need this class, something is probably wrong in your design. This definition should only serve the purpose of a null-value or to point to an erroneous state.
 */
template<typename ... Concepts>
struct NoDependencies {};

END_NAMESPACE