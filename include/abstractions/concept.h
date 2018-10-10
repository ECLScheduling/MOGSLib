#pragma once

#include <system/type_definitions.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief An abstraction to be extended by concrete concepts.
 */
class Concept {
public:
  /**
   * @brief A function to initialize all the concepts values and references to be used by the scheduler.
   * @details The init method will be called by MOGSLib before invoking the scheduler and after all the RTS data is set-up.
   */
  template<RuntimeSystemEnum T>
  void init() {}
};

END_NAMESPACE
