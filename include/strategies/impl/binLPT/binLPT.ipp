template<typename InputAdaptor>
void Strategy<InputAdaptor>::doTaskMapping() {
  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;

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
  auto PE_heap = input.PEIds();
  LoadComp comp;

  comp.loads = &(input.PELoads());

  std::make_heap(PE_heap.begin(), PE_heap.end(), comp);

  for(auto i : chunk_ordered_indexes) {
    auto task_vector = &(load_info->chunks->tasks[i]);

    //TODO: Why is this working?? PE_heap.front() is oddly working
    algorithmMapped(task_vector, PE_heap.front(), load_info->chunks->load_sum[i]); // As the algorithm uses a heap, the index of the PE that receives the next task chunk will be always 0.
    std::pop_heap(PE_heap.begin(), PE_heap.end(), comp);
    std::cout << "After pop_head: " << std::endl;
    for(auto peid : PE_heap) {
      std::cout << "PE id: " << peid << " (" << input.PELoads()[peid] << ")" << std::endl;
    }
    std::push_heap(PE_heap.begin(), PE_heap.end(), comp);
    std::cout << "After push_head: " << std::endl;
    for(auto peid : PE_heap) {
      std::cout << "PE id: " << peid << " (" << input.PELoads()[peid] << ")" << std::endl;
    }
  }
}