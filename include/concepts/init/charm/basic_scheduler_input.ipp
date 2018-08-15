BEGIN_NAMESPACE(Concept)

template<>
void BasicSchedulerInput::init<MOGSLib::Abstraction::RuntimeSystemEnum::Charm>() {
  auto input = MOGSLib::RTS::Charm::stats;

  auto nPEs = input->nprocs();
  auto nTasks = input->n_objs;

  auto *map = new int[nPEs];

  // Add the available processors into the vector of processors in the input.
  for(auto pe = 0; pe < nPEs; ++pe) {
    map[pe] = -1;
    if(input->procs[pe].available) {
      map[pe] = PE_ids.size();

      PE_ids.push_back(pe);
      PEs.push_back(input->procs[pe].bg_walltime);
    }
  }

    // Add the migrateable tasks to the vector of tasks and add the load of the non migrateable tasks to the adequate processor.
  for(auto task = 0; task < nTasks; ++task) {
    LDObjData &taskData = input->objData[task];
    auto pe = input->from_proc[task]; // Get the PE's id where the task is allocated.
      
    if(taskData.migratable) {
      const auto load = taskData.wallTime * input->procs[pe].pe_speed; // Calculate the load of a Task.
      tasks.push_back(taskData.wallTime * input->procs[pe].pe_speed);// Add the task load to the data array.
      task_ids.push_back(task);// Add the task id to the data array.
    } else {
      pe = map[pe];

      assert(pe != -1); // Nonmigrateable task on an unavailable processor.

      PEs[pe] += taskData.wallTime; //_PEVector[pe].totalLoad() += taskData.wallTime;
    }
  }

  delete [] map;
}

END_NAMESPACE