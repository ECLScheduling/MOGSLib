#include <concepts/implementation/workload_aware_input.h>
#include <rts/charm.h>

BEGIN_NAMESPACE(Concept)

template<MOGSLib::Abstraction::RuntimeSystemEnum T>
void temp_func_aware(WorkloadAwareInput& concept) {}

template<>
void temp_func_aware<MOGSLib::Abstraction::RuntimeSystemEnum::Charm>(WorkloadAwareInput& concept) {
  auto input = MOGSLib::RTS::Charm::stats;

  auto nPEs = input->nprocs();
  auto nTasks = input->n_objs;

  auto *map = new int[nPEs];

  // Add the available processors into the vector of processors in the input.
  for(auto pe = 0; pe < nPEs; ++pe) {
    map[pe] = -1;
    if(input->procs[pe].available) {
      map[pe] = concept.PE_ids.size();

      concept.PE_ids.push_back(pe);
      concept.PEs.push_back(input->procs[pe].bg_walltime);
    }
  }

    // Add the migrateable tasks to the vector of tasks and add the load of the non migrateable tasks to the adequate processor.
  for(auto task = 0; task < nTasks; ++task) {
    LDObjData &taskData = input->objData[task];
    auto pe = input->from_proc[task]; // Get the PE's id where the task is allocated.
      
    if(taskData.migratable) {
      const auto load = taskData.wallTime * input->procs[pe].pe_speed; // Calculate the load of a Task.
      concept.tasks.push_back(taskData.wallTime * input->procs[pe].pe_speed);// Add the task load to the data array.
      concept.task_ids.push_back(task);// Add the task id to the data array.
    } else {
      pe = map[pe];

      assert(pe != -1); // Nonmigrateable task on an unavailable processor.

      concept.PEs[pe] += taskData.wallTime; //_PEVector[pe].totalLoad() += taskData.wallTime;
    }
  }

  delete [] map;
}

template<>
struct Driver<WorkloadAwareInput, MOGSLib::Abstraction::RuntimeSystemEnum::Charm> {
  using Initializer = void (*)(WorkloadAwareInput&);

  static constexpr Initializer initializer = temp_func_aware<MOGSLib::Abstraction::RuntimeSystemEnum::Charm>;
};

END_NAMESPACE