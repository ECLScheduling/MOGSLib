#pragma once

#include <system/traits.h>
#include <adaptors/charm/charmTypes.h>
#include <strategies/binLPT/binLPTStrategy.h>
#include <adaptors/charm/charmAdaptorWithGenericStructure.h>

using UInt = CharmTypes::UInt;
using Load = CharmTypes::Load;

using Adaptor = CharmAdaptorWithGenericStructure<Uint>;
using Strategy = BinLPT::Strategy<Adaptor>;