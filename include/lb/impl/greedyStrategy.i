// #############################################
// Implementation of the GreedyStrategy methods.
// #############################################

template<typename InputType>
inline void GreedyStrategy<InputType, true>::createPEHeap(const InputType &input) {
  auto peIdSet = input.getPEsIds();

  PEs = MinHeap();
  for(auto it = peIdSet.begin(); it != peIdSet.end(); ++it)
    PEs.push(LoadBearer(*it,0));
}

template<typename InputType>
inline void GreedyStrategy<InputType, true>::createTaskHeap(const InputType &input) {
  auto taskIdSet = input.getTasksIds();

  tasks = MaxHeap();
  for(auto it = taskIdSet.begin(); it != taskIdSet.end(); ++it)
    tasks.push(LoadBearer(*it, input.getTaskLoad(*it)));
}

template<typename InputType>
void GreedyStrategy<InputType, true>::doWork(const InputType &input) {
  createPEHeap(input);
  createTaskHeap(input);

  if(PEs.empty())
    return;

  while(!tasks.empty()) {
    const LoadBearer task = tasks.top();
    const LoadBearer PE = PEs.top();

    tasks.pop();
    PEs.pop();

    PEs.push(LoadBearer(PE.id, PE.load + task.load));

    this->lbOutput.set(task.id, PE.id);
  }
}

// #############################################
// Implementation of the GreedyStrategyInitialLoad methods.
// #############################################

template<typename InputType>
void GreedyStrategyInitialLoad<InputType, true>::createPEHeap(const InputType &input) {
  auto peIdSet = input.getPEsIds();

  this->PEs = this->MinHeap();
  for(auto it = peIdSet.begin(); it != peIdSet.end(); ++it)
    this->PEs.push(LoadBearer(*it,input.getPELoad(*it)));
}