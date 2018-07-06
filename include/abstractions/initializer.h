#pragma once

#include "rts_representation.h"

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief A general interface for creating specialized initializers for concrete adapters.
 */
template<RuntimeSystemEnum TargetRTS, typename Adapter>
struct Initializer {
  using RTSData = RTS<TargetRTS>;

  /**
   * @brief This method is used to initialize a given concrete adapter in the context of a RuntimeSystem.
   */
  static void init(Adapter *adapter) {}
};

END_NAMESPACE