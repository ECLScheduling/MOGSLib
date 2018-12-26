#include <gtest/gtest.h>

#include <policies/greedy.h>
#include <policy_tests/workload_aware_input_base.h>

/**
 *  @class GreedyPolicyTests
 *  @brief A suite of unit tests for the Greedy policy.
 */
class GreedyPolicyTests : public WorkloadAwarePolicyTests {
public:
  /// @brief Set the Policy type to Greedy.
  using Policy = MOGSLib::Policy::Greedy<Deps>;

  /// @brief a proxy function to call the policy's map function.
  void execute_policy() {
    Policy::map(map, input.tasks, input.pus);
  }

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    WorkloadAwarePolicyTests::SetUp();
  }

};

/// @brief Test if a single task is correctly assigned to the single processor.
TEST_F(GreedyPolicyTests, single_task) {
  set_pus_and_tasks(1,1);

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

/// @brief Test if the processors recieve the tasks in decreasing workload order.
TEST_F(GreedyPolicyTests, single_task_two_PEs) {
  set_pus_and_tasks(2,1);

  input.pus[0] = 20;
  input.pus[1] = 10;

  execute_policy();
  ASSERT_EQ(1, map[0]); // The most unloaded one.
}

/// @brief Test if each task is assigned to a unique processor if both share the same initial load state.
TEST_F(GreedyPolicyTests, two_task_equally_loaded_PEs) {
  set_pus_and_tasks(2,2);

  input.tasks[0] = 10;
  input.tasks[1] = 10;

  input.pus[0] = 10;
  input.pus[1] = 10;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]);
}

/// @brief Test if multiple tasks are assigned to a processor if it is still the most underloaded.
TEST_F(GreedyPolicyTests, two_task_unequally_loaded_PEs) {
  set_pus_and_tasks(2,2);

  input.tasks[0] = 10;
  input.tasks[1] = 10;

  input.pus[0] = 0;
  input.pus[1] = 30;

  execute_policy();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
}

/// @brief Test if multiple tasks assignments can change the most underloaded processor.
TEST_F(GreedyPolicyTests, three_task_unequally_loaded_PEs) {
  set_pus_and_tasks(2,3);

  input.tasks[0] = 10;
  input.tasks[1] = 10;
  input.tasks[2] = 10;

  input.pus[0] = 0;
  input.pus[1] = 19;

  execute_policy();
  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,1,0)
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[0]);
}

/// @brief Test if tasks with different load are assigned in decreasing order.
TEST_F(GreedyPolicyTests, tasks_unequal_workload) {
  set_pus_and_tasks(2,3);

  input.tasks[0] = 20;
  input.tasks[1] = 10;
  input.tasks[2] = 30;

  input.pus[0] = 0;
  input.pus[1] = 40;

  execute_policy();
  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,0,1)
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]); 
}