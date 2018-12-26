#include <gtest/gtest.h>

#include <policy_tests/minimal_input_base.h>
#include <policies/task_pack.h>

/**
 *  @class TaskPackPolicyTests
 *  @brief A suite of unit tests for the TaskPack policy.
 */
class TaskPackPolicyTests : public MinimalInputPolicyTests {
public:
  /// @brief Set the Policy type to TaskPack.
  using Policy = MOGSLib::Policy::TaskPack<Deps>;

  Id npacks;

  /// @brief a proxy function to call the policy's map function.
  void execute_policy() {
    Policy::map(map, input.tasks, input.pus, npacks);
  }
  
  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    npacks = 0;
    MinimalInputPolicyTests::SetUp();
  }
};

/// @brief Trivial test for the policy.
TEST_F(TaskPackPolicyTests, single_task) {
  set_pus_and_tasks(1, 1);
  npacks = 1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

/// @brief Test if the policy can handle more packs than tasks available.
TEST_F(TaskPackPolicyTests, single_task_two_packs) {
  set_pus_and_tasks(1, 1);
  npacks = 2;

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

/// @brief Test if all the tasks are associated with the same processor if they are all packed together.
TEST_F(TaskPackPolicyTests, two_tasks_two_PEs_one_pack) {
  set_pus_and_tasks(2, 2);
  npacks = 1;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

/// @brief Test if each task is assigned individually if there is as much packs as there are tasks.
TEST_F(TaskPackPolicyTests, two_tasks_two_PEs_two_pack) {
  set_pus_and_tasks(2, 2);
  npacks = 2;

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}


/// @brief Test if the policy is aware of leftovers from unexact division.
TEST_F(TaskPackPolicyTests, odd_tasks_even_packs) {
  set_pus_and_tasks(3, 5);
  npacks = 3;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(2, map[4]);
}

/// @brief Test if the policy can assign multiple packs to the same PU.
TEST_F(TaskPackPolicyTests, less_PUs_than_packs) {
  set_pus_and_tasks(2, 5);
  npacks = 3;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(0, map[4]);
}

/// @brief Test if the policy ignores PUs if there are less packs than PUs.
TEST_F(TaskPackPolicyTests, more_PEs_than_packs) {
  set_pus_and_tasks(4, 5);
  npacks = 2;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}