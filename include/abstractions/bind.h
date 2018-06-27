#pragma once

/**
 * @brief This abstraction, when specialized, is responsible for binding abstract concepts with pointers to concrete adapters.
 */
template<typename T>
struct Bind {
  static void bind() {}
};