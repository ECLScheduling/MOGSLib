#include <gtest/gtest.h>

#include <policies/greedy/policy.h>

using Index = Policy::Index;
using Load = Policy::Load;
using TaskMap = Policy::TaskMap;
using TaskEntry = Policy::TaskEntry;

using SchedulingPolicy = Policy::Greedy<>;

class GreedyPolicyTests : public ::testing::Test {
public:

  TaskMap map;
  Index ntasks, nPEs;
  Load *task_loads, *PE_loads;

  void setPEs(const Index &n) {
    nPEs = n;
    PE_loads = new Load[nPEs]();
  }

  void setTasks(const Index &n) {
    ntasks = n;
    task_loads = new Load[ntasks]();
    map = new TaskEntry[ntasks]();
  }

  void execute_policy() {
    SchedulingPolicy::map(map, ntasks, task_loads, nPEs, PE_loads);
  }

  void SetUp() {
    map = nullptr;
    ntasks = 0;
    nPEs = 0;
    task_loads = nullptr;
    PE_loads = nullptr;
  }

  void TearDown() {
    if(task_loads != nullptr) {
      delete [] task_loads;
      task_loads = nullptr;
    }
    if(PE_loads != nullptr) {
      delete [] PE_loads;
      PE_loads = nullptr;
    }
    if(map != nullptr) {
      delete [] map;
      map = nullptr;
    }
  }

};

TEST_F(GreedyPolicyTests, single_task) {
  setTasks(1);
  setPEs(1);

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

TEST_F(GreedyPolicyTests, single_task_two_PEs) {
  setTasks(1);
  setPEs(2);

  PE_loads[0] = 20;
  PE_loads[1] = 10;

  execute_policy();
  ASSERT_EQ(1, map[0]); // The most unloaded one.
}

TEST_F(GreedyPolicyTests, two_task_equally_loaded_PEs) {
  setTasks(2);
  setPEs(2);

  task_loads[0] = 10;
  task_loads[1] = 10;

  PE_loads[0] = 10;
  PE_loads[1] = 10;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]);
}

TEST_F(GreedyPolicyTests, two_task_unequally_loaded_PEs) {
  setTasks(2);
  setPEs(2);

  task_loads[0] = 10;
  task_loads[1] = 10;

  PE_loads[0] = 0;
  PE_loads[1] = 30;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
}

TEST_F(GreedyPolicyTests, three_task_unequally_loaded_PEs) {
  setTasks(3);
  setPEs(2);

  task_loads[0] = 10;
  task_loads[1] = 10;
  task_loads[2] = 10;

  PE_loads[0] = 0;
  PE_loads[1] = 19;

  execute_policy();
  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,1,0)
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[0]);
}

TEST_F(GreedyPolicyTests, tasks_unequal_workload) {
  setTasks(3);
  setPEs(2);

  task_loads[0] = 20;
  task_loads[1] = 10;
  task_loads[2] = 30;

  PE_loads[0] = 0;
  PE_loads[1] = 40;

  execute_policy();
  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,0,1)
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]); 
}