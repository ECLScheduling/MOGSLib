#pragma once

#include <abstractions/rts/openmp/traits.h>

struct Lulesh2 {
  using Id = typename MOGSLib::SystemTraits<MOGSLib::System::libgomp>::Id;
  using Load = typename MOGSLib::SystemTraits<MOGSLib::System::libgomp>::Load;
};