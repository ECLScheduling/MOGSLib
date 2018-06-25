#pragma once

#ifdef RTS_IS_CHARM

#include <vector>

#include <interfaces/adaptor/defaultAdaptor.h>
#include "charmTypes.h"
#include <cassert>

// Charm++ specific includes.
#include <ckgraph.h>
#include <CentralLB.h>

/**
 * @brief This class is the implementation of the AdaptorInterface to be linked in the Charm environment.
 * @details This class presents basic translation from Charm++ datatypes to generic input for load balancing strategies.
 */
class CharmAdaptorDefault : public DefaultAdaptor<CharmTypes::Load, CharmTypes::UInt> {
public:

  using LDStats = BaseLB::LDStats;

  std::vector<UInt> task_ids;
  std::vector<UInt> pe_ids;

protected:

  /**
   * @variable input A reference the Charm's LDStats instance.
   */
  LDStats *input;

  /**
   * @variable loads_pe The loads of every PE.
   */
  std::vector<Load> pe_loads;

  /**
   * @variable loads_tasks The loads of every task.
   */
  std::vector<Load> task_loads;
  

  /**
   * Populates the internal vectors that will be used to implement the interface methods.
   */
  void readCharmData(){
    int nPEs = input->nprocs();
    int nTasks = input->n_objs;

    int *map = new int[nPEs];

    // Add the available processors into the vector of processors in the input.
    for(auto pe = 0; pe < nPEs; ++pe) {
      map[pe] = -1;
      if(input->procs[pe].available) {
        map[pe] = pe_ids.size();

        pe_ids.push_back(static_cast<UInt>(pe));
        pe_loads.push_back(input->procs[pe].bg_walltime); //_PEVector[pe].totalLoad() +=  _PEVector[pe].overhead();
      }
    }

    // Add the migrateable tasks to the vector of tasks and add the load of the non migrateable tasks to the adequate processor.
    for(auto task = 0; task < nTasks; ++task) {
      LDObjData &taskData = input->objData[task];
      auto pe = input->from_proc[task]; // Get the PE's id where the task is allocated.
      
      if(taskData.migratable) {
        const Load load = taskData.wallTime * input->procs[pe].pe_speed; // Calculate the load of a Task.
        task_loads.push_back(taskData.wallTime * input->procs[pe].pe_speed);// Add the task load to the data array.
        task_ids.push_back(static_cast<UInt>(task));// Add the task id to the data array.

      } else {
        pe = map[pe];

        assert(pe != -1); // Nonmigrateable task on an unavailable processor.

        pe_loads[pe] += taskData.wallTime; //_PEVector[pe].totalLoad() += taskData.wallTime;
      }
    }

    delete [] map;
  }

public:

  /**
   * The constructor funcion of this class. It is used to initialize it's internal state.
   * @param stats The collected usefull data for load balancing, given by the Charm++ run time system.
   */
  CharmAdaptorDefault(LDStats *stats) : input(stats) {
    readCharmData();
  }

  /**
   * @return A vector of loads for the PEs
   */
  inline Load* PELoads() {
    return pe_loads.data();
  }

  /**
   * @return A vector of loads for the tasks.
   */
  inline Load* taskLoads() {
    return task_loads.data();
  }

  /**
   * @return The amount of PEs in the input.
   */
  inline UInt nPEs() {
    return pe_loads.size();
  }

  /**
   * @return The amount of tasks in the input.
   */
  inline UInt ntasks() {
    return task_loads.size();
  }

};

#endif