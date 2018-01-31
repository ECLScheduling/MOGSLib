#include <gtest/gtest.h>

#include <strategies/binLPT/binLPT.h>

#include <interfaces/adaptor/defaultAdaptor.h>
#include <interfaces/adaptor/extensions/withGenericStructure.h>

#include <system/traits.h>

namespace BinLPT_Strategy_Test {

using UInt = Traits<void>::UInt;
using Load = UInt;

class TestInputAdaptor : public DefaultAdaptor<Load>, public WithGenericStructure<UInt> {
public:

  std::vector<Load> pe_loads;
  std::vector<Load> task_loads;
  UInt k;

  /**
   * @brief A method to obtain the additional input structure.
   */
  inline UInt& structure() {
    return k;
  }

  /**
   * @return A vector of loads for the PEs
   */
  inline std::vector<Load>& PELoads() { 
    return pe_loads;
  }

  /**
   * @return A vector of loads for the tasks.
   */
  inline std::vector<Load>& taskLoads() {
    return task_loads;
  }

  virtual ~TestInputAdaptor() {}

};

/**
 * @brief This class is a helper class to test the BinLPT task mapping function.
 */
class StrategyTest : public ::testing::Test {
public:

  using Strategy = BinLPT::Strategy<TestInputAdaptor>;
  using Output = Strategy::Output;

  TestInputAdaptor *input;
  Output output;
  Strategy *strategy;

  UInt ntasks;
  UInt npes;
  Load *tasks;

  void callTestFunction() {
    output = strategy->mapTasks(*input);
  }

  void allocTasks() {
    tasks = new Load[ntasks];
  }

  void initPEs(UInt n) {
    for(UInt i = 0; i < n; ++i)
      input->pe_loads.push_back(0);
  }

  void initTasks(UInt n) {
    for(UInt i = 0; i < n; ++i)
      input->task_loads.push_back(tasks[i]);
  }

  void buildInput(UInt k) {
    input->k = k;
    initTasks(ntasks);
    initPEs(npes);
  }

  void SetUp() {
    input = new TestInputAdaptor();
    strategy = new Strategy();

    tasks = nullptr;
  }

  void TearDown() {
    if(input != nullptr){
      delete input;
      input = nullptr;
    }
    if(strategy != nullptr){
      delete strategy;
      strategy = nullptr;
    }
    if(tasks != nullptr){
      delete [] tasks;
      tasks = nullptr;
    }
  }
};

TEST_F(StrategyTest, emptyInput) {
  input->k = 1;
  callTestFunction();

  EXPECT_EQ(output.map.size(), 0);
}

TEST_F(StrategyTest, oneTask) {
  ntasks = 1;
  npes = 1;
  const UInt k = 1;

  allocTasks();
  tasks[0] = 10;
  buildInput(k);

  callTestFunction();

  EXPECT_EQ(output.map.size(), 1); // Only one PE got tasks.
  EXPECT_EQ(output.map[0].size(), ntasks); // The PE only got one task.
  EXPECT_EQ(output.map[0].at(0), 0); // The task that the PE got is the first one.
}

TEST_F(StrategyTest, twoTasks) {
  ntasks = 2;
  npes = 1;
  const UInt k = 1;

  allocTasks();
  tasks[0] = 10;
  tasks[1] = 20;
  buildInput(k);

  callTestFunction();

  EXPECT_EQ(output.map.size(), 1); // Only one PE got tasks.
  EXPECT_EQ(output.map[0].size(), ntasks); // The PE only got two tasks.
  EXPECT_EQ(output.map[0].at(0), 0); // The task that the PE got is the first one and the second.
  EXPECT_EQ(output.map[0].at(1), 1); // The task that the PE got is the first one and the second.
}

TEST_F(StrategyTest, twoTasksTwoChunksOnePE) {
  ntasks = 2;
  npes = 1;
  const UInt k = 2;

  allocTasks();
  tasks[0] = 20;
  tasks[1] = 10;
  buildInput(k);

  callTestFunction(); // Loads = 20, 10; load/chunk = 15

  EXPECT_EQ(output.map.size(), 1); // Only one PE got tasks.
  EXPECT_EQ(output.map[0].size(), ntasks); // The PE only got two tasks.
  EXPECT_EQ(output.map[0].at(0), 0); // The task that the PE got is the first one and the second.
  EXPECT_EQ(output.map[0].at(1), 1); // The task that the PE got is the first one and the second.
}

TEST_F(StrategyTest, twoTasksTwoChunksTwoPE) {
  ntasks = 2;
  npes = 2;
  const UInt k = 2;

  allocTasks();
  tasks[0] = 20;
  tasks[1] = 10;
  buildInput(k);

  callTestFunction(); // Loads = 20, 10; load/chunk = 15

  ASSERT_EQ(output.map.size(), npes); // Both PEs got tasks.

  EXPECT_EQ(output.map[0].size(), 1); // Each got one task.
  EXPECT_EQ(output.map[1].size(), 1); // Each got one task.
}

TEST_F(StrategyTest, twoTasksTwoChunksTwoPE_OtherCase) {
  ntasks = 2;
  npes = 2;
  const UInt k = 2;

  allocTasks();
  tasks[0] = 10;
  tasks[1] = 20;
  buildInput(k);

  callTestFunction(); // Loads = 10, 20; load/chunk = 15; First chunk will take up both tasks

  EXPECT_EQ(output.map.size(), 1); // Only one chunk, thus only one PE gets all the load.

  EXPECT_EQ(output.map[0].size(), ntasks); // First PE got all the tasks.
}

TEST_F(StrategyTest, taskSetTest) {
  ntasks = 20;
  npes = 4;
  const UInt k = 8;

  allocTasks();
  for(UInt i = 0; i < ntasks; ++i)
    tasks[i] = ntasks-i;
  buildInput(k);

  callTestFunction(); // Loads = [19..1]; load/chunk = 26;

  // Chunks = [20,19], [18,17], [16,15], [14,13], [12,11,10], [9,8,7,6], [5,4,3,2,1], []
  // PEs / Chunk = [0] [1,6] [2,5] [3,4]

  EXPECT_EQ(output.map.size(), npes); // All pes have tasks

  EXPECT_EQ(output.map[0].size(), 2); // 20, 19
  EXPECT_EQ(output.map[1].size(), 7); // 18, 17, 5, 4, 3, 2, 1
  EXPECT_EQ(output.map[2].size(), 5); // 12, 11, 10, 14, 13
  EXPECT_EQ(output.map[3].size(), 6); // 16, 15, 9, 8, 7, 6
}

TEST_F(StrategyTest, highImbalance) {
  ntasks = 20;
  npes = 4;
  const UInt k = 4;

  allocTasks();
  for(UInt i = 0; i < k; ++i) {
    tasks[i] = ntasks;
  }
  for(UInt i = k; i < ntasks; ++i)
    tasks[i] = 1;
  buildInput(k);

  callTestFunction(); // Loads = 20,20,20,20,1,1,1,...; load/chunk = 24;

  // Chunks = [20,20], [20,20], [1,1,1,...,1], []
  // PEs / Chunk = [0] [1] [2] []

  EXPECT_EQ(output.map.size(), npes-1); // All pes but one will have tasks because it will have less chunks than PEs

  EXPECT_EQ(output.map[0].size(), 2);
  for(auto task : output.map[0])
    EXPECT_EQ(tasks[task], 20);
  EXPECT_EQ(output.map[1].size(), 2);
  for(auto task : output.map[1])
    EXPECT_EQ(tasks[task], 20);
  EXPECT_EQ(output.map[2].size(), 16);
  for(auto task : output.map[2])
    EXPECT_EQ(tasks[task], 1);
  EXPECT_EQ(output.map[3].size(), 0);
}

TEST_F(StrategyTest, noImbalance) {
  ntasks = 20;
  npes = 4;
  const UInt k = 4;

  allocTasks();
  for(UInt i = 0; i < ntasks; ++i)
    tasks[i] = 1;
  buildInput(k);

  callTestFunction(); // Loads = 1,1,1,...,1; load/chunk = 5;

  // Chunks = [6x1], [6x1], [6x1], [2x1]
  // PEs / Chunk = [0] [1] [2] [3]

  EXPECT_EQ(output.map.size(), npes);

  EXPECT_EQ(output.map[0].size(), 6);
  EXPECT_EQ(output.map[1].size(), 6);
  EXPECT_EQ(output.map[2].size(), 6);
  EXPECT_EQ(output.map[3].size(), 2);
}


}