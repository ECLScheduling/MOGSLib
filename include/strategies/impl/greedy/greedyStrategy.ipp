// #############################################
// Implementation of the GreedyStrategy methods.
// #############################################

template<typename InputType>
inline void GreedyStrategy<InputType, true>::createPEHeap(const InputType &input) {
  auto peIdSet = input.getPEs();

  PEs = MinHeap();
  for(auto it = peIdSet.begin(); it != peIdSet.end(); ++it)
    PEs.push(LoadBearer(*it,0));
}

template<typename InputType>
inline void GreedyStrategy<InputType, true>::createTaskHeap(const InputType &input) {
  tasks = MaxHeap();

  for(auto task : input.getTasks())
    tasks.push(task);
}

template<typename InputType>
void GreedyStrategy<InputType, true>::doTaskMapping(const InputType &input) {

  // Create the heap data structures used by the strategy
  createPEHeap(input);
  createTaskHeap(input);

  // Doesnt make sense to balance a load to an empty set of processing units.
  if(PEs.empty())
    return;

  // Main greedy strategy loop.

  while(!tasks.empty()) {
    const LoadBearer task = tasks.top();
    LoadBearer PE = PEs.top();

    tasks.pop();
    PEs.pop();

    PE.load += task.load;

    PEs.push(PE);

    this->lbOutput.set(task.id, PE.id);
  }
}