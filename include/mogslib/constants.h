#pragma once

namespace MOGSLib {

/**
 * @brief An enumerate of all runtime systems which MOGSLib supports.
 */
enum System {
  charm,
  libgomp
};

/**
 * @brief A declaration of the system traits based on the System enumerate value.
 * @details This structure is meant to contain at least the Load and Id type definition defaults for the system.
 */
template<System R>
struct SystemTraits {};

}