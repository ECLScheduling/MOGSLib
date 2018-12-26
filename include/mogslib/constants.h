#pragma once

namespace MOGSLib {

enum System {
  charm,
  libgomp
};

template<System R>
struct SystemTraits {};

}