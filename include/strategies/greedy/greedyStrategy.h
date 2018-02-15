#pragma once

#include <system/debug.h>
#include <interfaces/strategy/strategyInterface.h>
#include <algorithms/greedy/greedyAlgorithm.h>

#include <vector>
#include <algorithm>

namespace Greedy {

/**
 * @brief This class encapsulates the implementation of a Greedy load balancer strategy.
 */
template <typename InputAdaptor>
class Strategy : public StrategyInterface<InputAdaptor> {
public:

  using Load = typename InputAdaptor::Load;
  using UInt = typename InputAdaptor::UInt;

  using AlgorithmSet = Algorithms<Load, UInt>;

  virtual ~Strategy() {}

protected:

  struct LoadBearer {
    Load load;
    UInt id;

    void operator =(const LoadBearer &t) {
      load = t.load;
      id = t.id;
    }

    bool operator >(const LoadBearer &t) const {
      return load > t.load;
    }

    bool operator <(const LoadBearer &t) const {
      return load < t.load;
    }
  };

  static inline bool maxCmp(const LoadBearer& a, const LoadBearer& b) {
    return a < b;
  }

  static inline bool minCmp(const LoadBearer& a, const LoadBearer& b) {
    return a > b;
  }

  /**
   * @brief The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   */
  void doTaskMapping();

};

#include "greedyStrategy.ipp"

}