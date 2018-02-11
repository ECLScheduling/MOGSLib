#include <gtest/gtest.h>

#include <interfaces/adaptor/defaultAdaptor.h>
#include <strategies/greedy/greedyStrategy.h>

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

TEST_F(StrategyTest, one_task_one_PE) {
  ntasks = 1;
  nPEs = 1;

  allocTasks();
  allocPEs();
  tasks[0] = 10;
  buildInput();

  callTestFunction();

  EXPECT_EQ(output[0], 0); // The PE only got one task.
}

TEST_F(StrategyTest, two_tasks_one_PE) {
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

TEST_F(StrategyTest, two_tasks_two_PEs) {
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

TEST_F(StrategyTest, two_tasks_two_PE_one_overloaded) {
  ntasks = 2;
  nPEs = 2;

  allocTasks();
  allocPEs();
  tasks[0] = 10;
  tasks[1] = 20;
  PEs[0] = 31;
  buildInput();

  callTestFunction();

  for(UInt i = 0; i < ntasks; ++i)
    EXPECT_EQ(output[i], 1); // Only the PE 1, which was underloaded got any PEs.
}

TEST_F(StrategyTest, PE_sorting) {
  ntasks = 2;
  nPEs = 2;

  allocTasks();
  allocPEs();
  tasks[0] = 20;
  tasks[1] = 10;
  PEs[0] = 11;
  buildInput();

  callTestFunction();

  EXPECT_EQ(output[0], 1); // The first PE was overloaded so the second got the first task.
  EXPECT_EQ(output[1], 0); // The load of the second PE was greater and the first PE got the second task.
}

TEST_F(StrategyTest, PE_sorting_not_needed) {
  ntasks = 2;
  nPEs = 2;

  allocTasks();
  allocPEs();
  tasks[0] = 1;
  tasks[1] = 9;
  PEs[0] = 11;
  buildInput();

  callTestFunction();

  EXPECT_EQ(output[0], 1); // The first PE was overloaded so the second got the first task.
  EXPECT_EQ(output[1], 1); // The load of the second PE was greater and the first PE got the second task.
  EXPECT_EQ(adaptor.pe_loads[0], 10);
  EXPECT_EQ(adaptor.pe_loads[1], 11);
}

TEST_F(StrategyTest, task_and_PE_sorting) {
  ntasks = 5;
  nPEs = 4;

  allocTasks();
  allocPEs();
  tasks[0] = 1;
  tasks[1] = 2;
  tasks[2] = 1;
  tasks[3] = 4;
  tasks[4] = 1;

  PEs[0] = 6;
  PEs[1] = 2;
  PEs[2] = 8;
  PEs[3] = 4;
  buildInput();

  callTestFunction(); // PE load order: (2, 4, 8, 6); Task load order: (4,2,1,1)

  EXPECT_EQ(output[0], 1); // First task load: 4; PE load order after: (4, 6, 8, 6)
  EXPECT_EQ(output[1], 3); // Second task load: 2; PE load order after: (6, 6, 8, 6)
  EXPECT_EQ(output[2], 3); // Third task load: 1; PE load order after: (6, 6, 8, 7)
  EXPECT_EQ(output[3], 1); // ...
  EXPECT_EQ(output[4], 0); // ...
  
}

}