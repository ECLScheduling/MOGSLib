#pragma once

#include <vector>

#include <abstractions/concept.h>

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

  /**
   * @brief A function to initialize all the concepts values and references to be used by the scheduler.
   * @details The init method will be called by MOGSLib before invoking the scheduler and after all the RTS data is set-up.
   */
  template<MOGSLib::Abstraction::RuntimeSystemEnum T>
  void init() {}
};