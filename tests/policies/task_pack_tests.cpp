#include <gtest/gtest.h>

#include <policies/task_pack.h>

using SchedulingPolicy = MOGSLib::Policy::TaskPack;
using Index = MOGSLib::Index;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

class TaskPackPolicyTests : public ::testing::Test {
public:
  Index ntasks;
  Index nPEs;
  Index npacks;
  TaskMap map;

  void execute_policy() {
    SchedulingPolicy::map(map, ntasks, nPEs, npacks);
  }

  void createMap(const Index &n) {
    ntasks = n;
    map = new TaskEntry[ntasks]();
  }

  void SetUp() {
    ntasks = 0;
    nPEs = 0;
    npacks = 0;
    map = nullptr;
  }

  void TearDown() {
    if(map != nullptr) {
      delete [] map;
      map = nullptr;
    }
  }
};

TEST_F(TaskPackPolicyTests, single_task) {
  createMap(1);
  nPEs = 1;
  npacks = 1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

TEST_F(TaskPackPolicyTests, single_task_two_packs) {
  createMap(1);
  nPEs = 1;
  npacks = 2;

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

TEST_F(TaskPackPolicyTests, two_tasks_two_PEs_one_pack) {
  createMap(2);
  nPEs = 2;
  npacks = 1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

TEST_F(TaskPackPolicyTests, two_tasks_two_PEs_two_pack) {
  createMap(2);
  nPEs = 2;
  npacks = 2;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

TEST_F(TaskPackPolicyTests, odd_tasks_even_packs) {
  createMap(5);
  nPEs = 3;
  npacks = 3;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(2, map[4]);
}

TEST_F(TaskPackPolicyTests, less_PEs_than_packs) {
  createMap(5);
  nPEs = 2;
  npacks = 3;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(0, map[4]);
}

TEST_F(TaskPackPolicyTests, more_PEs_than_packs) {
  createMap(5);
  nPEs = 4;
  npacks = 2;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}