#include <gtest/gtest.h>

#include <interfaces/adaptor/defaultAdaptor.h>
#include <strategies/greedy/greedyStrategy.h>
#include <system/debug.h>

namespace Greedy_Tests {

using UIntType = Traits<DefaultTypes>::UInt;
using LoadType = UIntType;

/**
 * @brief A dummy adaptor that extends a real adaptor to test the Greedy Strategy.
 */
class TestInputAdaptor : public DefaultAdaptor<LoadType, UIntType> {
public:

  using UInt = UIntType;
  using Load = UInt;

  std::vector<Load> pe_loads;
  std::vector<Load> task_loads;

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
 * @brief This class is a helper class to test the Greedy Strategy.
 */
class StrategyTest : public ::testing::Test {
public:

  using UInt = UIntType;
  using Load = UInt;

  using Strategy = Greedy::Strategy<TestInputAdaptor>;

  TestInputAdaptor adaptor;
  Strategy strategy;

  UInt ntasks, nPEs;
  Load *tasks, *PEs;

  UInt *output;

  void SetUp() {
    output = nullptr;
    tasks = nullptr;
    PEs = nullptr;
  }

  void TearDown() {
    if(output != nullptr) {
      delete [] output;
      output = nullptr;
    }
    if(tasks != nullptr) {
      delete [] tasks;
      tasks = nullptr;
    }
    if(PEs != nullptr) {
      delete [] PEs;
      PEs = nullptr;
    }
  }

  void allocTasks() {
    tasks = new Load[ntasks]();
  }

  void allocPEs() {
    PEs = new Load[nPEs]();
  }

  void initTasks_test1() {
    for(UInt i = 0; i < ntasks; ++i)
      tasks[i] = ntasks+1;
  }

  void buildInput() {
    for(UInt i = 0; i < ntasks; ++i)
      adaptor.task_loads.push_back(tasks[i]);
    for(UInt i = 0; i < nPEs; ++i)
      adaptor.pe_loads.push_back(PEs[i]);
  }

  inline void callTestFunction() {
    output = strategy.mapTasks(&adaptor);
  }

};

TEST_F(StrategyTest, oneTask) {
  ntasks = 1;
  nPEs = 1;

  allocTasks();
  allocPEs();
  tasks[0] = 10;
  buildInput();

  callTestFunction();

  EXPECT_EQ(output[0], 0); // The PE only got one task.
}

TEST_F(StrategyTest, twoTasks) {
  ntasks = 2;
  nPEs = 1;

  allocTasks();
  allocPEs();
  tasks[0] = 10;
  tasks[1] = 10;
  buildInput();

  callTestFunction();

  EXPECT_EQ(output[0], 0); // The PE got both tasks.
  EXPECT_EQ(output[1], 0); // The PE got both tasks.
}

TEST_F(StrategyTest, twoTasksTwoChunksOnePE) {
  ntasks = 2;
  nPEs = 2;

  allocTasks();
  allocPEs();
  tasks[0] = 10;
  tasks[1] = 10;
  buildInput();

  callTestFunction();

  EXPECT_EQ(output[0], 0); // Each PE got one task.
  EXPECT_EQ(output[1], 1); // Each PE got one task.
}

}