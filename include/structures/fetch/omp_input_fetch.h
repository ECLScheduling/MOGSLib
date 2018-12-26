#pragma once

#include <abstractions/rts/openmp.h>

namespace MOGSLib { namespace Functionality {

struct OpenMPInput {
  template<typename I>
  static inline void fetch(I& input) {}
};

}}