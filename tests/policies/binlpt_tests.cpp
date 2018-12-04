#include <gtest/gtest.h>

#include "../type_definitions.h"
#include <policies/binlpt.h>

#include <memory>

using Load = MOGSLib::Load;
using Index = MOGSLib::Index;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

using SchedulingPolicy = MOGSLib::Policy::BinLPT<Load>;

struct LoadGenerator {
  template<Load L>
  static inline Load constant(const Index &i) { return L; }

  template<Index M>
  static inline Load decreasing(const Index &i) { return M-i; }

  static inline Load increasing(const Index &i) { return i; }
};

class BinlptPolicyTests : public ::testing::Test {
public:
  std::vector<Load> tasks, pus;
  Index k;

  std::unique_ptr<TaskMap> map;

  void SetUp() {
    tasks.clear();
    pus.clear();
    map.reset(nullptr);
  }

  auto execute_policy() {
    SchedulingPolicy::map(*map, tasks, pus, k);
    return *map;
  }

  void set_pus_and_tasks(const Index &p, const Index &t) {
    pus.resize(p);
    tasks.resize(t);
    map = std::make_unique<TaskMap>(new TaskEntry[t]);
  }

  void set_task_loads(Load (*gen)(const Index &)) {
    for(decltype(tasks.size()) i = 0; i < tasks.size(); ++i)
      tasks[i] = gen(i);
  }
};

TEST_F(BinlptPolicyTests, policy_regular_tasks_unloaded_PEs) {
  Index ntasks = 4;
  Index npus = 2;
  k = 2;

  set_pus_and_tasks(npus, ntasks);
  set_task_loads(LoadGenerator::constant<5>); // [5,5,5,5] => 0:[5,5] 1:[5,5] => assign order:{0,1}

  auto map_ref = execute_policy();
  EXPECT_EQ(1, map_ref[0]);
  EXPECT_EQ(1, map_ref[1]);
  EXPECT_EQ(0, map_ref[2]);
  EXPECT_EQ(0, map_ref[3]);
}

TEST_F(BinlptPolicyTests, policy_irregular_tasks_unloaded_pus) {
  Index ntasks = 5;
  Index npus = 2;
  k = 2;

  set_pus_and_tasks(npus, ntasks);
  set_task_loads(LoadGenerator::increasing); // [1,2,3,4,5] => 0:[1,2,3,4] 1:[5] => assign order:{0,1}

  auto map_ref = execute_policy();
  EXPECT_EQ(0, map_ref[0]);
  EXPECT_EQ(0, map_ref[1]);
  EXPECT_EQ(0, map_ref[2]);
  EXPECT_EQ(0, map_ref[3]);
  EXPECT_EQ(1, map_ref[4]);
}

TEST_F(BinlptPolicyTests, policy_irregular_tasks_decreasing_unloaded_pus) {
  Index ntasks = 5;
  Index npus = 2;
  k = 4;

  set_pus_and_tasks(npus, ntasks);
  set_task_loads(LoadGenerator::decreasing<5>); // [5,4,3,2,1] => 0:[5] 1:[4] 2:[3] 3:[2,1] => ordered:{0,1,3,2}

  auto map_ref = execute_policy();
  EXPECT_EQ(0, map_ref[0]);
  EXPECT_EQ(1, map_ref[1]);
  EXPECT_EQ(0, map_ref[2]);
  EXPECT_EQ(1, map_ref[3]);
  EXPECT_EQ(1, map_ref[4]);
}

TEST_F(BinlptPolicyTests, policy_regular_tasks_loaded_pus) {
  Index ntasks = 4;
  Index npus = 2;
  k = 2;

  set_pus_and_tasks(npus, ntasks);
  set_task_loads(LoadGenerator::constant<5>); // [5,5,5,5] => 0:[5,1] 1:[5,5] => ordered:{0,1}
  
  pus[0] = 7;

  auto map_ref = execute_policy();
  EXPECT_EQ(0, map_ref[0]);
  EXPECT_EQ(0, map_ref[1]);
  EXPECT_EQ(1, map_ref[2]);
  EXPECT_EQ(1, map_ref[3]);
}

TEST_F(BinlptPolicyTests, policy_irregular_tasks_loaded_pus) {
  Index ntasks = 5;
  Index npus = 4;
  k = 3;

  set_pus_and_tasks(npus, ntasks);
  set_task_loads(LoadGenerator::increasing); // [1,2,3,4,5] => 0:[1,2,3] 1:[4,5] 2:[] => ordered:{0,1}
  
  pus[0] = 7;

  auto map_ref = execute_policy();
  EXPECT_EQ(2, map_ref[0]);
  EXPECT_EQ(2, map_ref[1]);
  EXPECT_EQ(2, map_ref[2]);
  EXPECT_EQ(1, map_ref[3]);
  EXPECT_EQ(1, map_ref[4]);
}