#include <strategies/input/charm/charmAdaptor.h>

#ifdef RTS_IS_CHARM

void CharmAdaptor::populateVectors(){
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

#endif