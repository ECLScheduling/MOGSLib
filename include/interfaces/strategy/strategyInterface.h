#pragma once

#include <system/debug.h>

/**
 * @brief Class from which every load balancing strategy must inherit from. The StrategyInterface's input class must be provided at compile time.
 * @type InputAdaptor The input adaptor which serve as an interface to the input objects passed to the strategy.
 */
template<typename InputAdaptor>
class StrategyInterface {
public:

  using Input = InputAdaptor;
  using UInt = typename InputAdaptor::UInt;

protected:

  /**
   * @brief The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   */
  virtual void doTaskMapping() {}

  /**
   * @variable The current input being used in a strategy.
   */
  Input *currentInput;

public:

  /**
   * @variable A task map that indicates which processor is responsible for the task in the same index.
   *
   * @details If output[2] = 1 then the task[2] is mapped to pe[1].
   */
  UInt *output;


  StrategyInterface(){}

  virtual ~StrategyInterface() {}

  /**
   * @brief The main entrypoint for every strategy.
   *
   * @details This method does not clean the map if it was previously allocated.
   *
   * @param input The strategy's relevant input about the environment, architecture and tasks.
   *
   * @return The result task mapping given by the strategy.
   */
  UInt* mapTasks(InputAdaptor *input) {
    currentInput = input;
    output = new UInt[input->ntasks()]();

    doTaskMapping();

    currentInput = nullptr;
    return output;
  }

protected:

};

