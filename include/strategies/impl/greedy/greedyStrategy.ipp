#include <vector>
#include <algorithm>

template<typename InputAdaptor>
void GreedyStrategy<InputAdaptor>::doTaskMapping(InputAdaptor &input) {
  MaxHeap taskHeap;
  MinHeap PEHeap;

  MaxHeapComparator maxHeapCmp(StrategyInterface<InputAdaptor>::currentInput);
  MinHeapComparator minHeapCmp(StrategyInterface<InputAdaptor>::currentInput);

  GreedyAlgorithm algorithm;

  auto nTasks = input.taskCount();
  auto nPEs = input.PECount();

  if(nTasks == 0 || nPEs == 0)
    return;

  for(UInt i = 0; i < nTasks; ++i)
    taskHeap.push_back(i);
  for(UInt i = 0; i < nPEs; ++i)
    PEHeap.push_back(i);

  algorithm.template map<MaxHeapComparator, MinHeapComparator>(taskHeap, PEHeap, this, maxHeapCmp, minHeapCmp);
}