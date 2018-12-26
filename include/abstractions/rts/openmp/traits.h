#pragma once

#include <mogslib/constants.h>

namespace MOGSLib {

template<>
struct SystemTraits<System::openmp> {
  using Id = unsigned;
  using Load = unsigned;
};

}