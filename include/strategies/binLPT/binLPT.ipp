template<typename InputAdaptor>
void Strategy<InputAdaptor>::doTaskMapping() {
  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;

  /**
   * Initialize the vector of Ids.
   */
  PE_ids.clear();
  for(UInt i = 0; i < input.PELoads().size(); ++i) {
    PE_ids.push_back(i);  
  }
  clearLoadInfo();

  load_info = LoadInfo::analyzeLoadArray(input.taskLoads(), input.structure());
  
  assignPhase(partitioningPhase());
}

template<typename InputAdaptor>
std::vector<typename Strategy<InputAdaptor>::UInt> Strategy<InputAdaptor>::partitioningPhase() {
  AlgorithmSet::partitionChunks(*load_info);

  return AlgorithmSet::sortChunks(*load_info);
}

template<typename InputAdaptor>
void Strategy<InputAdaptor>::assignPhase(const std::vector<UInt> chunk_ordered_indexes) {
  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;
  
  LoadComp comp;
  comp.loads = &(input.PELoads());

  // Create a heap of indices to access the actual PE information
  std::make_heap(PE_ids.begin(), PE_ids.end(), comp);

  for(auto i : chunk_ordered_indexes) {
    auto task_vector = &(load_info->chunks->tasks[i]);

    // Assign the chunk to the PE in the heap front.
    assignChunk(task_vector, PE_ids.front(), load_info->chunks->load_sum[i]);

    // Update the PE's position in the heap without taking the value out of the list.
    std::pop_heap(PE_ids.begin(), PE_ids.end(), comp);
    std::push_heap(PE_ids.begin(), PE_ids.end(), comp);
  }
}

template<typename InputAdaptor>
void Strategy<InputAdaptor>::assignChunk(const std::vector<UInt> *task_indexes, const UInt &PE_index, const Load &total_load){
  auto &output = StrategyInterface<InputAdaptor>::strategyOutput;
  auto &input = StrategyInterface<InputAdaptor>::currentInput;

  // Set the mapping as part of the output.
  for(auto task : *task_indexes){
    output.set(PE_index, task);
  }
    
  // Adjust the PE load.
  input->PELoads()[PE_index] += total_load;
}