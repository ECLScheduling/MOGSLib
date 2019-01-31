#pragma once

#include <abstractions/rts/openmp/traits.h>

struct OmpDelayTest {
  using Id = typename MOGSLib::SystemTraits<MOGSLib::System::libgomp>::Id;
  using Load = typename MOGSLib::SystemTraits<MOGSLib::System::libgomp>::Load;
};