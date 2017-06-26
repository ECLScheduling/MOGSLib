#pragma once

#include <strategies/output/migrationElement.h>
#include <system/static.h>
#include <utility>
#include <chrono>
#include <ctime>
#include <iostream>

/**
 * Class that wraps commom performance analytics for strategy analysss.
 * @type StrategySetupModule A module that is coupled with the strategy analyzer to create the strategy instance and it's input.
 */
template<typename StrategySetupModule>
class StrategyAnalyzer {

protected:

  typedef decltype(std::declval<StrategySetupModule>().createStrategy(0,0)) Strategy;
  typedef decltype(std::declval<StrategySetupModule>().createInput(0,0)) Input;

  /**
   * An instance of the module that must be capable of generating the input and strategy instances.
   */
  StrategySetupModule module;

  /**
   * The pointer to the allocated input for the strategy.
   */
  Input input;

  /**
   * The pointer to the allocated strategy that will be analyzed.
   */
  Strategy strategy;

  /**
   * A flag to control if the input and strategy variables have been set.
   */
  bool allocatedResources;

  /**
   * Clear the memory of the previous test run.
   */
  void destroyPreviousRun() {
    if(allocatedResources) {
      delete input;
      delete strategy;
    }
  }

public:

  /**
   * The default StrategyAnalyser constructor.
   */
  StrategyAnalyzer() {
    allocatedResources = false;
  }

  ~StrategyAnalyzer() {
    destroyPreviousRun();
  }

  /**
   * Run the analyzer and collect data about the strategy.
   * @detailed This captures and forwards the main function's parameters to the StrategySetupModule.
   */
  void analyze(int argc, char *argv[]) {
    destroyPreviousRun();
    
    input = module.createInput(argc, argv);
    strategy = module.createStrategy(argc, argv);
    allocatedResources = true;

    //Start of the Task Mapping Analysis.
    std::chrono::system_clock::time_point before = std::chrono::system_clock::now();
    MigrationElement output = strategy->mapTasks(*input);
    std::chrono::system_clock::time_point after = std::chrono::system_clock::now();
    //End of the Task Mapping Analysis.

    std::cout << "Strategy mapping time: " << std::chrono::duration_cast<std::chrono::microseconds>(after - before).count() << "us." << std::endl;
  }

};