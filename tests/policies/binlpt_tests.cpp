#include <gtest/gtest.h>
#include <memory>

#include <type_definitions.h>
#include <load_generator.h>

#include <policies/binlpt.h>

using Index = MOGSLib::Index;
using Load = MOGSLib::Load;
using TaskEntry = MOGSLib::TaskEntry;
using TaskMap = MOGSLib::TaskMap;

/**
 *  @class BinlptPolicyTests
 *  @brief A suite of unit tests for the BinLPT policy.
 */
class BinlptPolicyTests : public ::testing::Test {
public:
  using LoadGenerator = UnitTest::LoadGenerator<Index, Load>;
  using Policy = MOGSLib::Policy::BinLPT<Load>;
  
  std::vector<Load> tasks, pus;
  std::unique_ptr<TaskMap> map;
  Index k;

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    tasks.clear();
    pus.clear();
    map.reset(nullptr);
  }

  /// @brief a proxy function to call the policy's map function.
  auto execute_policy() {
    Policy::map(*map, tasks, pus, k);
    return *map;
  }

  /**
   *  @brief Set the data about pu amount and task amount.
   *  @param p The amount of pus in the system.
   *  @param t The amount of tasks in the system.
   */
  void set_pus_and_tasks(const Index &p, const Index &t) {
    pus.resize(p);
    tasks.resize(t);
    map = std::make_unique<TaskMap>(new TaskEntry[t]);
  }

  /**
   *  @brief Set the workload of the tasks.
   *  @param gen A function to generate the load of a task given its index.
   */
  void set_task_loads(Load (*gen)(const Index &)) {
    for(decltype(tasks.size()) i = 0; i < tasks.size(); ++i)
      tasks[i] = gen(i);
  }
};

/**
 *  @brief Test if the policy work as intended when PUs are unloaded
 */
TEST_F(BinlptPolicyTests, policy_regular_tasks_unloaded_PUs) {
  k = 2;
  set_pus_and_tasks(2, 4);
  set_task_loads(LoadGenerator::regular<5>); // [5,5,5,5] => 0:[5,5] 1:[5,5] => assign order:{0,1}

  auto map_ref = execute_policy();
  EXPECT_EQ(0, map_ref[0]);
  EXPECT_EQ(0, map_ref[1]);
  EXPECT_EQ(1, map_ref[2]);
  EXPECT_EQ(1, map_ref[3]);
}

/**
 *  @brief Test if the policy work as intended when tasks are irregular and declared in increasing order.
 */
TEST_F(BinlptPolicyTests, policy_irregular_tasks_unloaded_pus) {
  k = 2;

  set_pus_and_tasks(2, 5);
  set_task_loads(LoadGenerator::increasing); // [1,2,3,4,5] => 0:[1,2,3,4] 1:[5] => assign order:{0,1}

  auto map_ref = execute_policy();
  EXPECT_EQ(0, map_ref[0]);
  EXPECT_EQ(0, map_ref[1]);
  EXPECT_EQ(0, map_ref[2]);
  EXPECT_EQ(0, map_ref[3]);
  EXPECT_EQ(1, map_ref[4]);
}

/**
 *  @brief Test if the policy work as intended when tasks are irregular and declared in decreasing order.
 */
TEST_F(BinlptPolicyTests, policy_irregular_tasks_decreasing_unloaded_pus) {
  k = 4;

  set_pus_and_tasks(2, 5);
  set_task_loads(LoadGenerator::decreasing<5>); // [5,4,3,2,1] => 0:[5] 1:[4] 2:[3] 3:[2,1] => ordered:{0,1,2,3}

  auto map_ref = execute_policy();
  EXPECT_EQ(0, map_ref[0]);
  EXPECT_EQ(1, map_ref[1]);
  EXPECT_EQ(1, map_ref[2]);
  EXPECT_EQ(0, map_ref[3]);
  EXPECT_EQ(0, map_ref[4]);
}

/**
 *  @brief Test if the policy function with previously-loaded PUs.
 */
TEST_F(BinlptPolicyTests, policy_regular_tasks_loaded_pus) {
  k = 2;

  set_pus_and_tasks(2, 4);
  set_task_loads(LoadGenerator::regular<5>); // [5,5,5,5] => 0:[5,5] 1:[5,5] => ordered:{0,1}
  
  pus[0] = 7;

  auto map_ref = execute_policy();
  EXPECT_EQ(1, map_ref[0]);
  EXPECT_EQ(1, map_ref[1]);
  EXPECT_EQ(0, map_ref[2]);
  EXPECT_EQ(0, map_ref[3]);
}

/**
 *  @brief Test if the policy function with previously-loaded PUs and irregular tasks.
 */
TEST_F(BinlptPolicyTests, policy_irregular_tasks_loaded_pus) {
  k = 3;

  set_pus_and_tasks(4, 5);
  set_task_loads(LoadGenerator::increasing); // [1,2,3,4,5] => 0:[1,2,3] 1:[4,5] => ordered:{1,0}
  
  pus[0] = 7;

  auto map_ref = execute_policy();
  EXPECT_EQ(2, map_ref[0]);
  EXPECT_EQ(2, map_ref[1]);
  EXPECT_EQ(2, map_ref[2]);
  EXPECT_EQ(1, map_ref[3]);
  EXPECT_EQ(1, map_ref[4]);
}

/**
 *  @brief Test if the policy function with previously-loaded PUs and irregular tasks declared in a decreasing order.
 */
TEST_F(BinlptPolicyTests, policy_irregular_tasks_loaded_pus_decreasing) {
  k = 3;

  set_pus_and_tasks(2, 5);
  set_task_loads(LoadGenerator::decreasing<5>); // [5,4,3,2,1] => 0:[5] 1:[4,3] 2:[2,1] => ordered:{1,0,2}
  
  pus[0] = 7;

  auto map_ref = execute_policy();
  EXPECT_EQ(0, map_ref[0]);
  EXPECT_EQ(1, map_ref[1]);
  EXPECT_EQ(1, map_ref[2]);
  EXPECT_EQ(1, map_ref[3]);
  EXPECT_EQ(1, map_ref[4]);
}