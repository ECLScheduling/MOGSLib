#pragma once

#include <vector>

BEGIN_NAMESPACE(Concept)

/**
 * @brief A concrete concept that fulfills both PEData and TaskData concepts.
 */
template<typename Ktype = MOGSLib::Index>
struct KValue : public Abstraction::Concept {
public:
  Ktype _k;

  /**
   * @brief Get a K value.
   */
  static inline Ktype k() {
    return _k;
  }
};

END_NAMESPACE