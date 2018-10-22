#include <gtest/gtest.h>

#include "../type_definitions.h"
#include <policies/compact.h>

using SchedulingPolicy = MOGSLib::Policy::Compact;
using Index = MOGSLib::Index;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

class CompactPolicyTests : public ::testing::Test {
public:
  Index ntasks;
  Index nPEs;
  TaskMap map;

  void execute_policy() {
    SchedulingPolicy::map(map, ntasks, nPEs);
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

TEST_F(CompactPolicyTests, single_task) {
  createMap(1);
  nPEs = 1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

TEST_F(CompactPolicyTests, two_tasks_two_PEs) {
  createMap(2);
  nPEs = 2;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

TEST_F(CompactPolicyTests, two_tasks_one_PE) {
  createMap(2);
  nPEs = 1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

TEST_F(CompactPolicyTests, n_tasks) {
  auto n = 6;
  createMap(n);
  nPEs = 2;

  execute_policy();
  auto s = n/nPEs;
  for(Index j = 0; j < n/s; ++j)
    for(Index i = 0; i < s; ++i)
      ASSERT_EQ(j, map[j*s + i]);
}