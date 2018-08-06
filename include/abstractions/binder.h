#pragma once

#include <cassert>
#include <system/static.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief This abstraction, when specialized, is responsible for binding abstract concepts with pointers to concrete adapters.
 */
template<typename T>
struct Binder {
  static void bind() {}
};

END_NAMESPACE