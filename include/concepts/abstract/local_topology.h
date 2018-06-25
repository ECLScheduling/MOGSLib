#pragma once

namespace Concepts {

/**
 * @brief This class presents the concept of presenting local topology data through.
 */
template<typename Concrete>
class LocalTopology {
  Concrete *_c;

public:

  LocalTopology(Concrete &c) : _c(c) {}

  LocalTopology() : _c(new Concrete()) {}

  ~LocalTopology() { delete _c; }

  /**
   * @brief Gets the depth of the topology.
   */
  inline int depth() { return _c->depth(); }

  /**
   * @brief Gets the amount of objects in a given depth.
   */
  inline int objcount_in_depth(const int &depth) { return _c->objcount_in_depth(depth); }

};

}