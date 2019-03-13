#include <gtest/gtest.h>

#include <policy_tests/minimal_input_base.h>
#include <policies/round_robin.h>

/**
 *  @class RoundRobinTests
 *  @brief A suite of unit tests for the RoundRobin policy.
 */
class RoundRobinTests : public MinimalInputPolicyTests {
public:
  /// @brief Set the Policy type to RoundRobin.
  using Policy = MOGSLib::Policy::RoundRobin<Deps>;

  /// @brief a proxy function to call the policy's map function.
  void execute_policy() {
    Policy::map(map, input.tasks, input.pus);
  }
  
  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    MinimalInputPolicyTests::SetUp();
  }
};

/// @brief Trivial test with a single task and a processor.
TEST_F(RoundRobinTests, single_task) {
  set_pus_and_tasks(1, 1);

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

/// @brief Test if each processor receives a task.
TEST_F(RoundRobinTests, two_tasks) {
  set_pus_and_tasks(2, 2);

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

/// @brief Test the same processor recieves all the tasks if its is the only processor.
TEST_F(RoundRobinTests, two_tasks_one_PE) {
  set_pus_and_tasks(1, 2);

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

/// @brief Test if the first processor gets the last tasks if there is n-1 processors.
TEST_F(RoundRobinTests, tasks) {
  auto n = 3;
  set_pus_and_tasks(n-1, n);

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[input.pus]);
}