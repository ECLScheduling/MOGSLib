
template<typename InputAdaptor>
void Strategy<InputAdaptor>::doTaskMapping() {
  debug_trc<LibStrategies>() << "Entering Greedy Strategy Mapping...\n";

  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;
  auto &task_map = StrategyInterface<InputAdaptor>::task_map;
  auto &PE_map = StrategyInterface<InputAdaptor>::PE_map;

  /* Retrieve the input from the adaptor */
  Load *task_loads = input.taskLoads();
  const UInt ntasks = input.ntasks();

  Load *PE_loads = input.PELoads();
  const UInt nPEs = input.nPEs();

  /** Order the tasks in decrescent order and create a binary min-heap for the PEs **/
  StrategyInterface<InputAdaptor>::createInputMaps(ntasks, nPEs);
  AlgorithmSet::order_tasks(task_loads, ntasks, task_map);
  AlgorithmSet::order_PEs(PE_loads, nPEs, PE_map);

  /** Main Greedy Loop **/
  for(UInt i = 0; i < ntasks; ++i) {
    auto task_idx = task_map[i];
    auto PE_idx = PE_map[0]; // heap-top (peek)

    StrategyInterface<InputAdaptor>::output[task_idx] = PE_idx; // Set the output.
    PE_loads[0] += task_loads[i]; // Update the PE with the added task's load.
    AlgorithmSet::reorder_PEs(PE_loads, PE_map, nPEs); // heap-replace (better than pop + push)
  }

  for(UInt i = 0; i < nPEs; ++i)
    debug_trc<LibStrategies>() << "PE[" << PE_map[i] << "]: " << PE_loads[i] << "\n";

  debug_trc<LibStrategies>() << "Exiting Greedy Strategy Mapping...\n";
}