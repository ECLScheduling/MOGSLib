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

  /**
   * @brief The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   */
  void doTaskMapping();

};

#include "greedyStrategy.ipp"

}