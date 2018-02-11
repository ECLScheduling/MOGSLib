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

  /**
   * @variable PE_map A map that indicates the index of the PEs in the input PE_loads structure.
   *
   * @details This variable is used when strategies needs to sort PEs and later assign the correct index to an output. This information might be useful when composing strategies that sorts the PE data.
   */
  UInt *PE_map;

  /**
   * @variable task_map A map that indicates the index of the tasks in the input task_loads structure.
   *
   * @details This variable is used when strategies needs to sort tasks and later assign the correct index to an output. This information might be useful when composing strategies that sorts the tasks data.
   */
  UInt *task_map;

  StrategyInterface(){
    PE_map = nullptr;
    task_map = nullptr;
  }

  /**
   * @brief Free the memory allocated by the internal maps.
   */
  void cleanInternalMaps() {
    if(PE_map != nullptr) {
      delete [] PE_map;
      PE_map = nullptr;
    }
    if(task_map != nullptr) {
      delete [] task_map;
      task_map = nullptr;
    }
  }

  virtual ~StrategyInterface() {
    cleanInternalMaps();
  }

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

  /** 
   * @brief Creates and initializes the map of PEs with default values.
   *
   * @details This method does not clean the map if it was previously allocated.
   *
   * @param nPEs The amount of PEs.
   */
  inline void createPEMap(const UInt nPEs) {
    PE_map = new UInt[nPEs]();
    for(UInt i = 0; i < nPEs; ++i)
      PE_map[i] = i;
  }

  /** 
   * @brief Creates and initializes the map of tasks with default values.
   *
   * @param ntasks The amount of tasks.
   */
  inline void createTaskMap(const UInt ntasks) {
    task_map = new UInt[ntasks]();
    for(UInt i = 0; i < ntasks; ++i)
      task_map[i] = i;
  }


  /** 
   * @brief Creates and initializes the map of tasks and PEs with default values.
   *
   * @details This method cleans the maps if they were used before.
   *
   * @param ntasks The amount of tasks.
   * @param nPEs The amount of PEs.
   */
  inline void createInputMaps(const UInt ntasks, const UInt nPEs) {
    cleanInternalMaps();
    createPEMap(nPEs);
    createTaskMap(ntasks);
  }

};

