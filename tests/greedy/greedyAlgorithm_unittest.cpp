// #include "fixtures/greedyFixtures.h"

// namespace GreedyAlogorithmTests {

// // This test is for debugging purposes. It can also be run in order to check if the usage of the greedy algorithm is functioning in a proper way.
// TEST_F(AlgorithmTest, workingTest) {
//   for(auto i = 0; i < 50; ++i) {
//     tasks.id.push_back(i);
//     tasks.load.push_back(i);
//     maxHeap.push_back(i);
//   }

//   for(auto i = 0; i < 8; ++i) {
//     PEs.id.push_back(i);
//     PEs.load.push_back(0);
//     minHeap.push_back(i);
//   }

//   callMap();

//   #ifdef GREEDY_ALGORITHM_TEST_DEBUG

//   for(auto const &entry : callbackReceiver->mapping) {
//     std::cout << "PE[" << entry.first << "], load(" << PEs.load[entry.first] << "):\n\tTasks: ";
//     for(auto task : entry.second) {
//       std::cout << task << " ";  
//     }
//     std::cout << std::endl;
//   }
  
//   #endif
// }

// }