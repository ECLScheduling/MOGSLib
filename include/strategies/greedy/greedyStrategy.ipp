template<typename InputAdaptor>
void GreedyStrategy<InputAdaptor>::doTaskMapping() {
  InputAdaptor &input = *StrategyInterface<InputAdaptor>::currentInput;
  
  MaxHeap taskHeap;
  MinHeap PEHeap;

  MaxHeapComparator maxHeapCmp(&input);
  MinHeapComparator minHeapCmp(&input);

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