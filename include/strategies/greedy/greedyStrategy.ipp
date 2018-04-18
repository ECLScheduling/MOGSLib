
template<typename InputAdaptor>
void Strategy<InputAdaptor>::doTaskMapping() {
  /* Retrieve the input from the adaptor */
  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;

  Load *task_loads = input.taskLoads();
  Load *PE_loads = input.PELoads();
  std::vector<LoadBearer> tasks(input.ntasks());
  std::vector<LoadBearer> PEs(input.nPEs());
  
  for(UInt i = 0; i < tasks.size(); ++i) {
    tasks[i].load = task_loads[i];
    tasks[i].id = i;
  }

  for(UInt i = 0; i < PEs.size(); ++i) {
    PEs[i].load = PE_loads[i];
    PEs[i].id = i;
  }


  /** Order the tasks in decrescent order and create a binary min-heap for the PEs **/
  std::make_heap(tasks.begin(), tasks.end(), Strategy::maxCmp);
  std::make_heap(PEs.begin(), PEs.end(), Strategy::minCmp);

  /** Main Greedy Loop **/
  while(!tasks.empty()) {
    auto &task = tasks.front();
    auto &PE = PEs.front(); // heap-top (peek)

    StrategyInterface<InputAdaptor>::output[task.id] = PE.id; // Set the output.
    PE.load += task.load; // Update the PE with the added task's load.

    std::pop_heap(tasks.begin(), tasks.end(), Strategy::maxCmp);
    tasks.pop_back();
    std::pop_heap(PEs.begin(), PEs.end(), Strategy::minCmp);
    std::push_heap(PEs.begin(), PEs.end(), Strategy::minCmp);
  }
}