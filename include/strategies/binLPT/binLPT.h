#pragma once

#include "binLPTAdaptorRequirements.h"

#include <interfaces/strategy/strategyInterface.h>
#include <algorithms/binLPT/binLPTAlgorithm.h>

namespace BinLPT {

/**
 * @brief This class encapsulates the implementation of the BinLPT strategy.
 * @details The BinLPT strategy was originally designed for OpenMP to act as a loop scheduler.
 */
template <typename InputAdaptor>
class Strategy : public StrategyInterface<InputAdaptor> {
  static_assert(BinLPTAdaptorRequirements<InputAdaptor, typename InputAdaptor::UInt>::value, "Input Adaptor must implement the WithGenericStructure<UInt> adaptor extension using the same UInt as the remainder of the system. The default UInt is defined in Traits<void>.");

public: 

  using Load = typename InputAdaptor::Load;
  using UInt = typename InputAdaptor::UInt;

  using AlgorithmSet = Algorithms<Load, UInt>;

protected:

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   */
  void doTaskMapping();
};

#include "binLPT.ipp"

}