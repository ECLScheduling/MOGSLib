#include <vector>
#include <algorithm>

template<typename InputAdaptor>
void GreedyStrategy<InputAdaptor>::doTaskMapping(const InputAdaptor &input) {
  MaxHeap taskHeap;
  MinHeap PEHeap;
  GreedyAlgorithm algorithm;

  Task *tasks;
  PE *PEs;

  auto nTasks = input.taskCount();
  auto nPEs = input.PECount();

  if(nTasks == 0 || nPEs == 0)
    return;

  tasks = new Task[nTasks];
  PEs = new PE[nPEs];

  constructPEHeap(PEHeap, PEs, nPEs, input);
  constructTaskHeap(taskHeap, tasks, nTasks, input);

  algorithm.map(taskHeap, PEHeap);

  for(auto PE : PEHeap)
    AbstractStrategy<InputAdaptor>::strategyOutput.setMultiple(PE->id(), PE->tasks);

  delete [] tasks;
  delete [] PEs;
}

template<typename InputAdaptor>
void GreedyStrategy<InputAdaptor>::constructTaskHeap(MaxHeap &maxHeap, Task * const tasks, const UInt &nTasks, const InputAdaptor &input) {

  for(UInt i = 0; i < nTasks; ++i) {
    maxHeap.push_back(tasks+i);

    tasks[i].setId(i);
    tasks[i].setLoad(input.taskLoad(i));
  }
}

template<typename InputAdaptor>
void GreedyStrategy<InputAdaptor>::constructPEHeap(MinHeap &minHeap, PE * const PEs, const UInt &nPEs, const InputAdaptor &input) {
  
  for(UInt i = 0; i < nPEs; ++i) {
    minHeap.push_back(PEs+i);

    PEs[i].setId(i);
    PEs[i].setLoad(input.PELoad(i));
  }
}