#pragma once

#ifdef RTS_IS_OPENMP

#include "openmpTypes.h"
#include <interfaces/adaptor/defaultAdaptor.h>

/**
 * @brief This class is the implementation of the DefaultAdaptor to be linked in the OpenMP environment.
 *
 * @details This class presents basic translation from OpenMP datatypes to generic input for load balancing strategies.
 */
class OpenMPAdaptorDefault : public DefaultAdaptor<OpenMPTypes::Load, OpenMPTypes::UInt> {
protected:

  /**
   * @variable loads_pe The loads of every PE.
   */
  Load *_pe_loads;

  /**
   * @variable npes The amount of PEs in the input.
   */
  UInt _nPEs;

  /**
   * @variable loads_tasks The loads of every task.
   */
  Load *_task_loads;

  /**
   * @variable npes The amount of tasks in the input.
   */
  UInt _ntasks;

public:

  /**
   * @brief The constructor funcion of this class. It is used to initialize it's internal state.
   *
   * @param stats The collected usefull data for load balancing, given by the Charm++ run time system.
   */
  OpenMPAdaptorDefault() {
    _task_loads = nullptr;
    _pe_loads = nullptr;
  }

  /**
   * @brief Releases the memory used by this structure.
   *
   * @details This destructor does not free the memory of the tasks input as it is created outside of this class.
   */
  virtual ~OpenMPAdaptorDefault() {
    if(_pe_loads != nullptr) {
      delete [] _pe_loads;
      _pe_loads = nullptr;
    }
    if(_task_loads != nullptr) {
      _task_loads = nullptr;
    }
  }

  /**
   * @return A vector of loads for the PEs
   */
  inline Load* PELoads() {
    return _pe_loads;
  }

  /**
   * @return The amount of PEs in the input.
   */
  inline UInt nPEs() {
    return _nPEs;
  }

  /**
   * @return A vector of loads for the tasks.
   */
  inline Load* taskLoads() {
    return _task_loads;
  }

  /**
   * @return The amount of tasks in the input.
   */
  inline UInt ntasks() {
    return _ntasks;
  }

  /**
   * @brief Set the amount of PEs that are contained in the input.
   *
   * @param the_nPEs The amount of PEs.
   */
  void setPECount(UInt the_nPEs) {
    _pe_loads = new Load[the_nPEs]();
    _nPEs = the_nPEs;
  }

  /**
   * @brief Set the task loads of all tasks in the input.
   *
   * @param tasks The load value of all tasks.
   * @param ntasks The amount of tasks.
   */
  void setTasks(Load *tasks, UInt the_ntasks) {
    _task_loads = tasks;
    _ntasks = the_ntasks;
  }

};

#endif