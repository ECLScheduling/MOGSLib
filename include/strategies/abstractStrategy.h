#pragma once

#include <strategies/output/migrationElement.h>
#include <memory>
#include <system/traits.h>

/**
 * Class from which every load balancing strategy must inherit from. The AbstractStrategy's input class must be provided at compile time.
 */
template<typename LBInput>
class AbstractStrategy {
protected:

  /**
   * The MigrationElement object that every strategy needs to output a result.
   */
  MigrationElement lbOutput;

public:

  /**
   * The main entrypoint for every load balancing strategy.
   * @param input The strategy's relevant input about the environment, architecture and tasks.
   * @return The result task mapping given by the strategy.
   */
  const MigrationElement& mapTasks(const LBInput &input) {
    doTaskMapping(input);
    return lbOutput;
  }

  /**
   * The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   * @param input The Load Balancer's input
   */
  virtual void doTaskMapping(const LBInput &input) {}
};

