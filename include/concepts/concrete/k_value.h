#pragma once

#include <vector>

#include <system/type_definitions.h>

BEGIN_NAMESPACE(Adapter)

/**
 * @brief A concrete concept that fulfills both PEData and TaskData concepts.
 */
template<typename Ktype = MOGSLib::Index>
struct KValue {
  Ktype _k;

  /**
   * @brief Get a K value.
   */
  static inline Ktype k() {
    return _k;
  }
};