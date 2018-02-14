#pragma once

#define RTS_IS_CHARM

#include <system/traits.h>
#include <adaptors/charm/charmTypes.h>
#include <strategies/greedy/greedyStrategy.h>
#include <adaptors/charm/charmAdaptorDefault.h>

namespace MOGSLib {

using UInt = CharmTypes::UInt;
using Load = CharmTypes::Load;

using Adaptor = CharmAdaptorDefault;
using Strategy = Greedy::Strategy<Adaptor>;

}