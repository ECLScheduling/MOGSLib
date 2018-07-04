#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Concept)

/**
 * @brief This class presents the concept of presenting local topology data through.
 */
template<typename Concrete>
class LocalTopology {
  static Concrete *c;

public:
  /**
   * @brief Gets the depth of the topology.
   */
  static inline decltype(c->depth()) depth() { return _c->depth(); }

  /**
   * @brief Gets the amount of objects in a given depth.
   */
  static inline decltype(c->objcount_in_depth(0)) objcount_in_depth(const int &depth) { return _c->objcount_in_depth(depth); }
};

END_NAMESPACE