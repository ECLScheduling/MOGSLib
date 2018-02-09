#include <gtest/gtest.h>

#include <strategies/binLPT/binLPT.h>

#include <interfaces/adaptor/defaultAdaptor.h>
#include <interfaces/adaptor/extensions/withGenericStructure.h>

#include <system/traits.h>

namespace BinLPT_Strategy_Test {

using UIntType = Traits<void>::UInt;
using LoadType = UIntType;

class TestInputAdaptor : public DefaultAdaptor<LoadType, UIntType>, public WithGenericStructure<UIntType> {
public:

  using UInt = UIntType;
  using Load = UInt;

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
  inline Load* PELoads() { 
    return pe_loads.data();
  }

  /**
   * @return A vector of loads for the tasks.
   */
  inline Load* taskLoads() {
    return task_loads.data();
  }

  inline UInt nPEs() {
    return pe_loads.size();
  }

  inline UInt ntasks() {
    return task_loads.size();
  }

  virtual ~TestInputAdaptor() {}

};

/**
 * @brief This class is a helper class to test the BinLPT task mapping function.
 */
class StrategyTest : public ::testing::Test {
public:

  using Strategy = BinLPT::Strategy<TestInputAdaptor>;
  using UInt = UIntType;
  using Load = UInt;

  TestInputAdaptor *input;
  UInt *output;
  Strategy *strategy;

  UInt ntasks;
  UInt npes;
  Load *tasks;

  UInt *tasksum_pe;

  void calculate_tasksum() {
    tasksum_pe = new UInt[npes]();
    for(UInt i = 0; i < ntasks; ++i) {
      tasksum_pe[output[i]] += 1;
    }
  }

  void callTestFunction() {
    output = strategy->mapTasks(input);
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
    tasksum_pe = nullptr;
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
    if(tasksum_pe != nullptr){
      delete tasksum_pe;
      tasksum_pe = nullptr;
    }
  }
};

TEST_F(StrategyTest, oneTask) {
  ntasks = 1;
  npes = 1;
  const UInt k = 1;

  allocTasks();
  tasks[0] = 10;
  buildInput(k);

  callTestFunction();

  EXPECT_EQ(output[0], 0); // The PE only got one task.
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

  EXPECT_EQ(output[0], 0); // The task that the PE got is the first one and the second.
  EXPECT_EQ(output[1], 0); // The task that the PE got is the first one and the second.
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

  EXPECT_EQ(output[0], 0); // The task that the PE got is the first one and the second.
  EXPECT_EQ(output[1], 0); // The task that the PE got is the first one and the second.
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

  EXPECT_EQ(output[0], 0); // Each got one task.
  EXPECT_EQ(output[1], 1); // Each got one task.
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

  for(UInt i = 0; i < ntasks; ++i)
    EXPECT_EQ(output[i], 0); // First PE got all the tasks.
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

  calculate_tasksum();
  EXPECT_EQ(tasksum_pe[0], 2); // 20, 19
  EXPECT_EQ(tasksum_pe[1], 7); // 18, 17, 5, 4, 3, 2, 1
  EXPECT_EQ(tasksum_pe[2], 5); // 12, 11, 10, 14, 13
  EXPECT_EQ(tasksum_pe[3], 6); // 16, 15, 9, 8, 7, 6
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

  calculate_tasksum();
  EXPECT_EQ(tasksum_pe[0], 2);
  EXPECT_EQ(tasksum_pe[1], 2);
  EXPECT_EQ(tasksum_pe[2], 16);
  EXPECT_EQ(tasksum_pe[3], 0);
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

  calculate_tasksum();
  EXPECT_EQ(tasksum_pe[0], 6);
  EXPECT_EQ(tasksum_pe[1], 6);
  EXPECT_EQ(tasksum_pe[2], 6);
  EXPECT_EQ(tasksum_pe[3], 2);
}


}