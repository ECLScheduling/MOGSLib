// #############################################
// Implementation of the GreedyStrategy methods.
// #############################################

#include <iostream>

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

  // Create the heap data structures used by the strategy
  createPEHeap(input);
  createTaskHeap(input);

  // Doesnt make sense to balance a load to an empty set of processing units.
  if(PEs.empty())
    return;

  // Main greedy strategy loop.
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
void GreedyInitialLoadStrategy<InputType, true>::createPEHeap(const InputType &input) {
  auto peIdSet = input.getPEsIds();

  this->PEs = MinHeap();
  for(auto it = peIdSet.begin(); it != peIdSet.end(); ++it) {
    this->PEs.push(LoadBearer(*it, input.getPELoad(*it)));
  }
}