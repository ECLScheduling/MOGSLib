#pragma once

#include <type_definitions.h>

namespace UnitTest {

/**
 *  @class LoadGenerator
 *  @brief A basic load generator for simple unit tests for behavior and corretude.
 */
template<typename I = Index, typename L = Load>
struct LoadGenerator {

  /**
   *  @brief Generate a regular load.
   *  @tparam C A value for load.
   *  @param i This parameter is ignored.
   *  @return Always return C.
   */
  template<L C>
  static inline L regular(const I &i = 0) { return C; }

  /**
   *  @brief Generate a decreasing load based on a maximum value and an index.
   *  @tparam max The maximum load value to be generated.
   *  @param i The amount of generated loads.
   *  @return max - i.
   */
  template<L max>
  static inline L decreasing(const I &i = 0) { return max-i; }

  /**
   *  @brief Generate an increased load based on the index.
   *  @param i The amount of generated loads.
   *  @return i.
   */
  static inline L increasing(const I &i = 0) { return i+1; }
};

}