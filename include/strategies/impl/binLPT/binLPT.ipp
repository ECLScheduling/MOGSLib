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
void Strategy<InputAdaptor>::assignPhase(const std::vector<UInt> chunk_ordering) {
  AlgorithmSet::assignChunks(*load_info, chunk_ordering, this);
}