#pragma once

#include <strategies/strategyInterface.h>

/**
 * @brief This class encapsulates the implementation of the BinLPT strategy.
 * @details The BinLPT strategy was originally implemented for OpenMP to act as a loop scheduler.
 */
template <typename InputAdaptor>
class BinLPT : public StrategyInterface<InputAdaptor> {
public: 
  
  using Load = typename InputAdaptor::Load;
  using Id = typename InputAdaptor::Id;
  using UInt = typename InputAdaptor::UInt;

protected:

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The strategy's input
   */
  void doTaskMapping(InputAdaptor &input);

};

#include "BinLPT.ipp"