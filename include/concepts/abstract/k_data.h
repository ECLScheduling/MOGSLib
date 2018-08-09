#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Concept)

/**
 * @brief A concept that displays methods to gather the a generic K value.
 */
template<typename Concrete>
struct KData {
  static Concrete *concrete;

  /**
   * @brief Get a K value.
   */
  static inline decltype(concrete->ntasks()) k() {
    return concrete->k();
  }
};

template <typename Concrete>
Concrete* KData<Concrete>::concrete = nullptr;

END_NAMESPACE