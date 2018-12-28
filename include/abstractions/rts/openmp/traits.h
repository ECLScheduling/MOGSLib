#pragma once

#include <mogslib/constants.h>

namespace MOGSLib {

template<>
struct SystemTraits<System::libgomp> {
  using Id = unsigned;
  using Load = unsigned;
};

}