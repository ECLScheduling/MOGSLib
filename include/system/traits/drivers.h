#pragma once

#include <system/types.h>
#include <cstdint>

namespace MOGSLib {

template<typename Concept, RuntimeSystemEnum T>
struct DriverTraits {
  using Initializer = typename Driver<Concept, T>::Initializer<T>;
};

template<>

}