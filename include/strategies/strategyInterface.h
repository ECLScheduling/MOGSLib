#pragma once

#include <strategies/output/migrationElement.h>
#include <memory>
#include <system/traits.h>

/**
 * Class from which every load balancing strategy must inherit from. The StrategyInterface's input class must be provided at compile time.
 * @type InputAdaptor The input adaptor which serve as an interface to the input objects passed to the strategy.
 */
template<typename InputAdaptor>
class StrategyInterface {
public:

  using Input = InputAdaptor;
  using Output = MigrationElement<typename InputAdaptor::Id>;

protected:

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   */
  virtual void doTaskMapping() {}

  /**
   * The current input being used in a strategy.
   */
  Input *currentInput;

public:

  /**
   * The MigrationElement object that every strategy needs to output a result.
   */
  Output strategyOutput;

  /**
   * The main entrypoint for every strategy.
   * @param input The strategy's relevant input about the environment, architecture and tasks.
   * @return The result task mapping given by the strategy.
   */
  const Output& mapTasks(InputAdaptor &input) {
    currentInput = &input;
    
    doTaskMapping();

    currentInput = nullptr;
    return strategyOutput;
  }
};

