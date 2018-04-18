#pragma once

#include <interfaces/strategy/strategyInterface.h>
#include <system/debug.h>

namespace EagerMap {

/**
 * @brief A strategy that infers a good positioning for tasks based on the hardware topology and the communication graph of the tasks.
 * @details This strategy is based on the 2015 PDP conference paper entitled "An Efficient Algorithm for Communication-Based Task Mapping"
 */
template <typename InputAdaptor>
class Strategy : public StrategyInterface<InputAdaptor> {
public: 
  
  using Load = typename InputAdaptor::Load;
  using UInt = InputAdaptor::UInt;

  Strategy() : StrategyInterface<InputAdaptor>() {}
  virtual ~Strategy() {}

protected:

  /**
   * @brief The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   *
   * @param input The strategy's input
   */
  void doTaskMapping(InputAdaptor &input);

};

#include "EagerMap.ipp"

}