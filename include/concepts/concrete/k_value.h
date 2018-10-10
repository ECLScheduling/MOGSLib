#pragma once

#include <vector>

#include <abstractions/concept.h>

BEGIN_NAMESPACE(Concept)

/**
 * @brief A concept to represent a K value of some numeric type T.
 */
template<typename T>
struct K : public Abstraction::Concept {
  T* value;

  /**
   * @brief Get the k value.
   */
  inline T k() const {
    return *value;
  }

  /**
   * @brief A function to initialize all the concepts values and references to be used by the scheduler.
   * @details The init method will be called by MOGSLib before invoking the scheduler and after all the RTS data is set-up.
   */
  template<MOGSLib::Abstraction::RuntimeSystemEnum T = MOGSLib::TargetSystem>
  void init() {}
};

END_NAMESPACE