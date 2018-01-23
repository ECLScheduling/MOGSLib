#pragma once

#ifdef RTS_IS_CHARM

#include <vector>

#include "../interface/defaultAdaptor.h"
#include "charmTypes.h"
#include <cassert>

// Charm++ specific includes.
#include <ckgraph.h>
#include <CentralLB.h>

/**
 * This class is the implementation of the AdaptorInterface to be linked in the Charm environment.
 * @details This class presents basic translation from Charm++ datatypes to generic input for load balancing strategies.
 */
class CharmAdaptor : public DefaultAdaptor<CharmTypes> {
public:

  using LDStats = BaseLB::LDStats;

  /**
   * @type PEVector a definition of a vector of Charm's ProcInfo.
   */
  using PEVector = std::vector<ProcInfo>;

  /**
   * @type TaskVector a definition of a vector of Charm's Vertex.
   */
  using TaskVector = std::vector<Vertex>;

private:

  /**
   * @variable input A reference the Charm's LDStats instance.
   */
  LDStats *input;

  //TODO: _PEVector and _taskVector must be removed since they have become obsolete. However, internal charm++ calculations are made when those objects are created. As a result, these vectors must remain until the calculations are studied and replicated or invoked here. 

  /**
   * @variable _PEVector The vector of every available PE in the environment.
   */
  PEVector _PEVector;

  /**
   * @variable _taskVector The vector of every migrateable task in the environment.
   */
  TaskVector _taskVector;

  /**
   * @variable loads_pe The loads of every PE.
   */
  std::vector<Load> loads_pe;

  /**
   * @variable loads_tasks The loads of every task.
   */
  std::vector<Load> loads_tasks;

  /**
   * @variable ids_pe The ids of every pe.
   */
  std::vector<Id> ids_pe;

  /**
   * @variable ids_tasks The ids of every task.
   */
  std::vector<Id> ids_tasks;

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
        map[pe] = _PEVector.size();
        _PEVector.push_back(ProcInfo(pe, input->procs[pe].bg_walltime, 0.0, input->procs[pe].pe_speed, true)); // Add the PE to the vector of PEs.
      }
    }

    // Add the migrateable tasks to the vector of tasks and add the load of the non migrateable tasks to the adequate processor.
    for(auto task = 0; task < nTasks; ++task) {
      LDObjData &taskData = input->objData[task];
      auto pe = input->from_proc[task]; // Get the PE's id where the task is allocated.
      
      if(taskData.migratable) {
        const Load load = taskData.wallTime * input->procs[pe].pe_speed; // Calculate the load of a Task.
        _taskVector.push_back(Vertex(task, load, true, input->from_proc[task])); // Add the task to a vector of tasks.

      } else {
        pe = map[pe];

        assert(pe != -1); // Nonmigrateable task on an unavailable processor.

        _PEVector[pe].totalLoad() += taskData.wallTime;
      }
    }

    delete [] map;

    // Adds the overhead to the total load of a PE.
    for (auto pe = 0; pe < _PEVector.size(); pe++){
      _PEVector[pe].totalLoad() +=  _PEVector[pe].overhead();
    }
}

  void populateInputVectors() {
    UInt pe_count = _PEVector.size();
    UInt task_count = _taskVector.size();;

    ids_pe = std::vector<Id>(pe_count);
    loads_pe = std::vector<Load>(pe_count);

    loads_tasks = std::vector<Load>(task_count);
    ids_tasks = std::vector<Id>(task_count);

    for(UInt i = 0; i < pe_count; ++i) {
      loads_pe[i] = _PEVector[i].getTotalLoad();
      ids_pe[i] = _PEVector[i].getProcId();
    }

    for(UInt i = 0; i < task_count; ++i) {
      loads_tasks[i] = _taskVector[i].getVertexLoad();
      ids_tasks[i] = _taskVector[index].getVertexId()
    }
  }

public:

  /**
   * The constructor funcion of this class. It is used to initialize it's internal state.
   * @param stats The collected usefull data for load balancing, given by the Charm++ run time system.
   */
  CharmAdaptor(LDStats *stats) : input(stats) {
    readCharmData();
    populateInputVectors();
  }

  /**
   * @return A vector of loads for the PEs
   */
  inline std::vector<Load>& PELoads() {
    return loads_pe;
  }

  /**
   * @return A vector of ids for the PEs.
   */
  inline std::vector<Id>& PEIds() {
    return ids_pe;
  }

  /**
   * @return A vector of loads for the tasks.
   */
  inline std::vector<Load>& taskLoads() {
    return loads_tasks;
  }

  /**
   * @return A vector of Ids for the tasks.
   */
  inline std::vector<Id>& taskIds() {
    return ids_tasks;
  }

};

#endif