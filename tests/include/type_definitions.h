#pragma once

#include <system/traits.h>

using Typedef = MOGSLib::WorkloadPolicyTypedef<unsigned, unsigned>;

using Index = typename Typedef::Index;
using Load = typename Typedef::Load;
using Schedule = typename Typedef::Schedule;