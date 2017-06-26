// #############################################
// Implementation of the GreedyStrategyInitialLoad methods.
// #############################################

template<typename InputType>
void GreedyInitialLoadStrategy<InputType, true>::createPEHeap(const InputType &input) {

  this->PEs = MinHeap();
  for(auto PEid : input.getPEs()) {
    this->PEs.push(LoadBearer(PEid, input.getPELoad(PEid)));
  }
}