#pragma once 

#include <system/static.h>

namespace Definitions {

constexpr auto charmRTS = "Charm";
constexpr auto noRTS = "None";

}

#ifndef RTS
#define RTS Definitions::noRTS
#endif

#if static_functions::const_string_equal(RTS, Definitions::charmRTS)
#define RTS_IS_CHARM
#elif static_functions::const_string_equal(RTS, Definitions::noRTS)
#define RTS_IS_NONE
#endif
