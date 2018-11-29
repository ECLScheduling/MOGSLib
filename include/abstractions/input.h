#pragma once

#include <system/types.h>

namespace MOGSLib { namespace Scheduler {

/**
 * @brief The base abstraction for input concepts.
 */
template<MOGSLib::InputType T>
struct Input {};

}}