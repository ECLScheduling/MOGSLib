#include <gtest/gtest.h>

#include <iostream>
#include <policies/binlpt.h>
#include <policy_tests/workload_aware_input_base.h>

/**
 *  @class BinlptPolicyTests
 *  @brief A suite of unit tests for the BinLPT policy.
 */
class BinlptPolicyTests : public WorkloadAwarePolicyTests {
public:
  /// @brief Set the Policy type to BinLPT.
  using Policy = MOGSLib::Policy::BinLPT<Deps>;

  Id k;

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    WorkloadAwarePolicyTests::SetUp();
  }

  /// @brief a proxy function to call the policy's map function.
  void execute_policy() {
    Policy::map(map, input.tasks, input.pus, k);
  }
};

/**
 *  @brief Test if the policy work as intended when PUs are unloaded
 */
TEST_F(BinlptPolicyTests, policy_regular_tasks_unloaded_PUs) {
  k = 2;
  set_pus_and_tasks(2, 4);

  set_task_loads(LoadGenerator::regular<5>); // [5,5,5,5] => 0:[5,5,5] 1:[5] => assign order:{0,1}

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]); // Because the clause to keep adding to the same chunks is ">" and not ">="
  EXPECT_EQ(1, map[3]);
}

/**
 *  @brief Test if the policy work as intended when tasks are irregular and declared in increasing order.
 */
TEST_F(BinlptPolicyTests, policy_irregular_tasks_unloaded_pus) {
  k = 2;

  set_pus_and_tasks(2, 5);
  set_task_loads(LoadGenerator::increasing); // [1,2,3,4,5] => 0:[1,2,3,4] 1:[5] => assign order:{0,1}

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(0, map[3]);
  EXPECT_EQ(1, map[4]);
}

/**
 *  @brief Test if the policy work as intended when tasks are irregular and declared in decreasing order.
 */
TEST_F(BinlptPolicyTests, policy_irregular_tasks_decreasing_unloaded_pus) {
  k = 4;

  set_pus_and_tasks(2, 5);
  set_task_loads(LoadGenerator::decreasing<5>); // [5,4,3,2,1] => mean = 15/4 (3) => 0: [5], 1:[4], 2:[3,2], 3:[1] => assign order:{0,2,1,3}

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}

/**
 *  @brief Test if the policy function with previously-loaded PUs.
 */
TEST_F(BinlptPolicyTests, policy_regular_tasks_loaded_pus) {
  k = 2;

  set_pus_and_tasks(2, 4);
  set_task_loads(LoadGenerator::regular<5>); // [5,5,5,5] => 0:[5,5,5] 1:[5] => ordered:{0,1}
  
  input.pus[0] = 7;

  execute_policy();
  EXPECT_EQ(1, map[0]);
  EXPECT_EQ(1, map[1]);
  EXPECT_EQ(1, map[2]);
  EXPECT_EQ(0, map[3]);
}

/**
 *  @brief Test if the policy function with previously-loaded PUs and irregular tasks.
 */
TEST_F(BinlptPolicyTests, policy_irregular_tasks_loaded_pus) {
  k = 3;

  set_pus_and_tasks(4, 5);
  set_task_loads(LoadGenerator::increasing); // [1,2,3,4,5] => 0:[1,2,3] 1:[4,5] => ordered:{1,0}
  
  input.pus[0] = 7;

  execute_policy();
  EXPECT_EQ(2, map[0]);
  EXPECT_EQ(2, map[1]);
  EXPECT_EQ(2, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}

/**
 *  @brief Test if the policy function with previously-loaded PUs and irregular tasks declared in a decreasing order.
 */
TEST_F(BinlptPolicyTests, policy_irregular_tasks_loaded_pus_decreasing) {
  k = 3;

  set_pus_and_tasks(2, 5);
  set_task_loads(LoadGenerator::decreasing<5>); // [5,4,3,2,1] => 0:[5,4] 1:[3,2,1] 2:[] => ordered:{1,0,2}
  
  input.pus[0] = 7;

  execute_policy();
  EXPECT_EQ(1, map[0]);
  EXPECT_EQ(1, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(0, map[3]);
  EXPECT_EQ(0, map[4]);
}