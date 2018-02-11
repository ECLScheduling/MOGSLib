
template<typename InputAdaptor>
void Strategy<InputAdaptor>::doTaskMapping() {
  /* Retrieve the input from the adaptor */
  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;

  Load *task_loads = input.taskLoads();
  const UInt ntasks = input.ntasks();

  Load *PE_loads = input.PELoads();
  const UInt nPEs = input.nPEs();

  /** Order the tasks in decrescent order and create a binary min-heap for the PEs **/
  UInt *task_map = AlgorithmSet::order_tasks(task_loads, ntasks);
  UInt *PE_map = AlgorithmSet::order_PEs(PE_loads, nPEs);

  /** Main Greedy Loop **/
  for(UInt i = 0; i < ntasks; ++i) {
    auto task_idx = task_map[i];
    auto PE_idx = PE_map[0]; // heap-top (peek)
 
    StrategyInterface<InputAdaptor>::output[task_idx] = PE_idx; // Set the output.
    PE_loads[PE_idx] += task_loads[task_idx]; // Update the PE with the added task's load.
    AlgorithmSet::reorder_PEs(PE_loads, PE_map, nPEs); // heap-replace (better than pop + push)
  }
}