
template<typename Input>
typename Scheduler<Input>::Output Scheduler<Input>::map(Input &input) {
  // /* Retrieve the input from the adaptor */
  std::vector<LoadBearer> tasks(input.app.ntasks);
  std::vector<LoadBearer> PEs(input.platform.nPEs);
  Output output = new Index[input.app.ntasks];
  
  for(Index i = 0; i < tasks.size(); ++i) {
    tasks[i].load = input.app.task_loads[i];
    tasks[i].id = i;
  }

  for(Index i = 0; i < PEs.size(); ++i) {
    PEs[i].load = input.platform.PE_loads[i];
    PEs[i].id = i;
  }


  // /** Order the tasks in decrescent order and create a binary min-heap for the PEs **/
  std::make_heap(tasks.begin(), tasks.end(), Scheduler::maxCmp);
  std::make_heap(PEs.begin(), PEs.end(), Scheduler::minCmp);

  /** Main Greedy Loop **/
  while(!tasks.empty()) {
    auto &task = tasks.front();
    auto &PE = PEs.front(); // heap-top (peek)

    output[task.id] = PE.id; // Set the output.
    PE.load += task.load; // Update the PE with the added task's load.

    std::pop_heap(tasks.begin(), tasks.end(), Scheduler::maxCmp);
    tasks.pop_back();
    std::pop_heap(PEs.begin(), PEs.end(), Scheduler::minCmp);
    std::push_heap(PEs.begin(), PEs.end(), Scheduler::minCmp);
  }

  return output;
}