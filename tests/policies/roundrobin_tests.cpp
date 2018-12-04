#include <gtest/gtest.h>

#include <type_definitions.h>
#include <policies/round_robin.h>

using SchedulingPolicy = MOGSLib::Policy::RoundRobin;
using Index = MOGSLib::Index;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

class RoundRobinTests : public ::testing::Test {
public:
  Index ntasks;
  Index nPEs;
  TaskMap map;

  void execute_policy() {
    MOGSLib::Policy::RoundRobin::map(map, ntasks, nPEs);
  }

  void createMap(const Index &n) {
    ntasks = n;
    map = new TaskEntry[ntasks]();
  }

  void SetUp() {
    ntasks = 0;
    nPEs = 0;
    map = nullptr;
  }

  void TearDown() {
    if(map != nullptr) {
      delete [] map;
      map = nullptr;
    }
  }
};

TEST_F(RoundRobinTests, single_task) {
  createMap(1);
  nPEs = 1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

TEST_F(RoundRobinTests, two_tasks) {
  createMap(2);
  nPEs = 2;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

TEST_F(RoundRobinTests, two_tasks_one_PE) {
  createMap(2);
  nPEs = 1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

TEST_F(RoundRobinTests, n_tasks) {
  auto n = 3;
  createMap(n);
  nPEs = n-1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[nPEs]);
}