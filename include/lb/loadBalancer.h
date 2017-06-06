#pragma once

#include <lb/migrationElement.h>
#include <memory>
#include <system/traits.h>

/**
 * Class from which every load balancer must inherit from. The Load balancer's input class must be provided at compile time.
 */
template<typename LBInput>
class LoadBalancer {
protected:

  /**
   * The MigrationElement object that every load balancer needs to output a result.
   */
  MigrationElement lbOutput;

public:

  /**
   * The main entrypoint for every load balancer.
   * @param input The LB's relevant input about the environment, architecture and tasks.
   * @return The result task mapping given by the load balancer.
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

