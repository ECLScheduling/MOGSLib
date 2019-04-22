#include <gtest/gtest.h>

#include <policy_tests/minimal_input_base.h>
#include <model/policies/compact.h>

/**
 *  @class CompactPolicyTests
 *  @brief A suite of unit tests for the Compact policy.
 */
class CompactPolicyTests : public MinimalInputPolicyTests {
public:
  /// @brief Set the Policy type to Compact.
  using Policy = MOGSLib::Policy::Compact<Deps>;

  /// @brief a proxy function to call the policy's map function.
  void execute_policy() {
    Policy::map(map, input.tasks, input.pus);
  }
  
  /// @brief a proxy function to call the policy's map function.
  void SetUp() {
    MinimalInputPolicyTests::SetUp();
  }
};

/// @brief Test if compact can correctly assign one task to one processor.
TEST_F(CompactPolicyTests, one_task) {
  set_pus_and_tasks(1,1);

  execute_policy();
  ASSERT_EQ(0, map[0]);
}

/// @brief Test if compact can correctly assign one task to each of two processors.
TEST_F(CompactPolicyTests, tasks_pus) {
  set_pus_and_tasks(2, 2);

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

/// @brief Test if compact can correctly assign two tasks to the only processors.
TEST_F(CompactPolicyTests, tasks_less_pus) {
  set_pus_and_tasks(1, 2);

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

/// @brief Test if compact can correctly assign few tasks to more processors.
TEST_F(CompactPolicyTests, less_tasks_thapus) {
  set_pus_and_tasks(3, 2);

  execute_policy();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

/// @brief Test if compact can correctly assign multiple tasks to fewer processors.
TEST_F(CompactPolicyTests, more_than_two_tasks_for_each_pu) {
  set_pus_and_tasks(2, 6);

  execute_policy();
  auto s = input.tasks/input.pus;

  for(Id j = 0; j < input.tasks/s; ++j)
    for(Id i = 0; i < s; ++i)
      ASSERT_EQ(j, map[j*s + i]);
}