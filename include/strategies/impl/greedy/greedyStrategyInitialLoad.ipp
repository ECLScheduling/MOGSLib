// #############################################
// Implementation of the GreedyStrategyInitialLoad methods.
// #############################################

template<typename InputType>
void GreedyInitialLoadStrategy<InputType, true>::createPEHeap(const InputType &input) {
  auto peIdSet = input.getPEsIds();

  this->PEs = MinHeap();
  for(auto it = peIdSet.begin(); it != peIdSet.end(); ++it) {
    this->PEs.push(LoadBearer(*it, input.getPELoad(*it)));
  }
}