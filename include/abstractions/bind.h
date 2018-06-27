#pragma once

#include <cassert>

namespace MOGSLib {

/**
 * @brief This abstraction, when specialized, is responsible for binding abstract concepts with pointers to concrete adapters.
 */
template<typename T>
struct Binder {
  static void bind() {
    static_assert(false, "A Binder has to be specialized in order to link concepts.");
  }
};

}