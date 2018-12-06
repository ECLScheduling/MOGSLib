#pragma once

#include <system/types.h>

namespace MOGSLib { namespace Input {

/**
 *  @brief The base abstraction for input concepts.
 */
template<MOGSLib::InputEnum T, typename ... Typedefs>
struct Declaration {};

}}