#pragma once

#define RTS_IS_OPENMP

#include <system/traits.h>
#include <adaptors/openmp/openmpTypes.h>
#include <strategies/binLPT/binLPTStrategy.h>
#include <adaptors/openmp/openmpAdaptorWithGenericStructure.h>

namespace MOGSLib {

using UInt = OpenMPTypes::UInt;
using Load = OpenMPTypes::Load;

using Adaptor = OpenMPAdaptorWithGenericStructure<UInt>;
using Strategy = BinLPT::Strategy<Adaptor>;

}