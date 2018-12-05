#include <gtest/gtest.h>

#include <task_map_utils.h>
#include <policies/greedy.h>

using SchedulingPolicy = MOGSLib::Policy::Greedy<>;

class GreedyPolicyTests : public ::testing::Test {
public:

  UnitTest::TaskMapUtils map;
  std::vector<Load> tasks, pus;

  void set_pus(const Index &n) {
    pus.resize(n);
  }

  void set_tasks(const Index &n) {
    tasks.resize();
    map.alloc(n);
  }

  void execute_policy() {
    SchedulingPolicy::map(map, tasks, pus);
  }

  void SetUp() {
    map.clear();
    tasks.clear();
    pus.clear();
  }

};

TEST_F(GreedyPolicyTests, single_task) {
  set_tasks(1);
  set_pus(1);

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

TEST_F(GreedyPolicyTests, single_task_two_PEs) {
  set_tasks(1);
  set_pus(2);

  pus[0] = 20;
  pus[1] = 10;

  execute_policy();
  ASSERT_EQ(1, map[0]); // The most unloaded one.
}

TEST_F(GreedyPolicyTests, two_task_equally_loaded_PEs) {
  set_tasks(2);
  set_pus(2);

  tasks[0] = 10;
  tasks[1] = 10;

  pus[0] = 10;
  pus[1] = 10;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]);
}

TEST_F(GreedyPolicyTests, two_task_unequally_loaded_PEs) {
  set_tasks(2);
  set_pus(2);

  tasks[0] = 10;
  tasks[1] = 10;

  pus[0] = 0;
  pus[1] = 30;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
}

TEST_F(GreedyPolicyTests, three_task_unequally_loaded_PEs) {
  set_tasks(3);
  set_pus(2);

  tasks[0] = 10;
  tasks[1] = 10;
  tasks[2] = 10;

  pus[0] = 0;
  pus[1] = 19;

  execute_policy();
  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,1,0)
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[0]);
}

TEST_F(GreedyPolicyTests, tasks_unequal_workload) {
  set_tasks(3);
  set_pus(2);

  tasks[0] = 20;
  tasks[1] = 10;
  tasks[2] = 30;

  pus[0] = 0;
  pus[1] = 40;

  execute_policy();
  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,0,1)
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]); 
}