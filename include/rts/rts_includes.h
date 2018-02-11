#pragma once

#include <system/traits.h>
#include <adaptors/charm/charmTypes.h>
#include <strategies/greedy/greedyStrategy.h>
#include <adaptors/charm/charmAdaptorDefault.h>

using UInt = CharmTypes::UInt;
using Load = CharmTypes::Load;

using Adaptor = CharmAdaptorDefault;
using Strategy = Greedy::Strategy<Adaptor>;