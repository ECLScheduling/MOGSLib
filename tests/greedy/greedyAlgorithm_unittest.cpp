#include "fixtures/greedyFixtures.h"

namespace GreedyAlogorithmTests {
// This test is for debugging purposes. It can also be run in order to check if the usage of the greedy algorithm is functioning in a proper way.
TEST_F(AlgorithmTest, workingTest) {
  for(auto i = 0; i < 50; ++i) {
    maxHeap.push_back(new Task(i, i));
  }

  for(auto i = 0; i < 8; ++i) {
    minHeap.push_back(new PE(i));
  }

  algorithm.map(maxHeap, minHeap);

  while(!minHeap.empty()) {
    auto pe = minHeap.back();
    
    #if GREEDY_ALGORITHM_TEST_DEBUG
    std::cout << "PE[" << pe->anId << "] count: " << pe->mappedTasks.size() << ". Load: " << pe->aLoad << std::endl;
    for(auto task : pe->mappedTasks)
      std::cout << " " << task;
    std::cout << std::endl;
    #endif

    minHeap.pop_back();
    delete pe;
  }

  while(!maxHeap.empty()) {
    auto task = maxHeap.back();
    maxHeap.pop_back();

    delete task;
  }
}

}