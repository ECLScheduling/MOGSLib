#pragma once

#ifdef RTS_IS_CHARM

#include <vector>

#include "../adaptorInterface.h"
#include "charmTypes.h"
#include <cassert>

// Charm++ specific includes.
#include <ckgraph.h>
#include <CentralLB.h>

/**
 * This class is the implementation of the AdaptorInterface to be linked in the Charm environment.
 * @details This class presents basic translation from Charm++ datatypes to generic input for load balancing strategies.
 */
class CharmAdaptor : AdaptorInterface<CharmTypes> {
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

  /**
   * @variable _PEVector The vector of every available PE in the environment.
   */
  PEVector _PEVector;

  /**
   * @variable _taskVector The vector of every migrateable task in the environment.
   */
  TaskVector _taskVector;

  /**
   * Populates the internal vectors that will be used to implement the interface methods.
   */
  void populateVectors(){
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
    for (auto pe = 0; pe < _PEVector.size(); pe++)
      _PEVector[pe].totalLoad() +=  _PEVector[pe].overhead();
}

public:

  /**
   * The constructor funcion of this class. It is used to initialize it's internal state.
   * @param stats The collected usefull data for load balancing, given by the Charm++ run time system.
   */
  CharmAdaptor(LDStats *stats) : input(stats) {
    populateVectors();
  }

  /**
   * @param index The index of the PE.
   * @return The load of the index-th PE present in this input.
   */
  inline const Load PEload(const UInt &index) {
    return _PEVector[index].getTotalLoad();
  }

  /**
   * @param index The index of the PE.
   * @return The id of the PE.
  */
  inline const Id PEId(const UInt &index) {
   return _PEVector[index].getProcId();
  }

  /**
   * @return The ammount of PEs in the library's input.
   */
  inline const UInt PECount() {
    return _PEVector.size();
  }

  /**
   * @param index The index of the task.
   * @return The load of the index-th task present in this input.
   */
  inline const Load taskLoad(const UInt &index) {
    return _taskVector[index].getVertexLoad();
  }

  /**
   * @param index The index of the task.
   * @return The id of the task.
   */
  inline const Id taskId(const UInt &index) {
    return _taskVector[index].getVertexId();
  }
  
  /**
   * @return The ammount of tasks in the library's input.
   */
  inline const UInt taskCount() {
    return _taskVector.size();
  }

};

#endif