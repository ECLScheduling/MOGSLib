#pragma once

#define RTS_IS_CHARM

#include <system/traits.h>
#include <adaptors/charm/charmTypes.h>
#include <strategies/binLPT/binLPTStrategy.h>
#include <adaptors/charm/charmAdaptorWithGenericStructure.h>

namespace MOGSLib {

using UInt = CharmTypes::UInt;
using Load = CharmTypes::Load;

using Adaptor = CharmAdaptorWithGenericStructure<UInt>;
using Strategy = BinLPT::Strategy<Adaptor>;

}