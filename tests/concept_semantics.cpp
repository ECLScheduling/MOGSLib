#include <gtest/gtest.h>

#include <schedulers/greedy/scheduler.h>
#include <input/application/minimal.h>
#include <input/platform/minimal.h>

TEST(scheduler_input_concepts, can_be_complete) {
  Concepts::SchedulerInput<int, int, int> is_valid;

  is_valid.app = 2;
  is_valid.misc = 1;
  is_valid.platform = 1;

  ASSERT_EQ(is_valid.app, 2);
  ASSERT_EQ(is_valid.misc, 1);
  ASSERT_EQ(is_valid.platform, 1);
}

TEST(scheduler_input_concepts, can_lack_app_data) {
  Concepts::SchedulerInput<Concepts::NoApplicationData, int, int> is_valid;

  // is_valid.app = 2; // This expression is now invalidated.
  is_valid.misc = 1;
  is_valid.platform = 1;

  ASSERT_EQ(is_valid.misc, 1);
  ASSERT_EQ(is_valid.platform, 1);
}

TEST(scheduler_input_concepts, can_lack_platform_data) {
  Concepts::SchedulerInput<int, Concepts::NoPlatformData, int> is_valid;

  is_valid.app = 2;
  is_valid.misc = 1;
  // is_valid.platform = 1; // This expression is now invalidated.

  ASSERT_EQ(is_valid.app, 2);
  ASSERT_EQ(is_valid.misc, 1);
}

TEST(scheduler_input_concepts, can_lack_misc_data) {
  Concepts::SchedulerInput<int, int> is_valid;

  is_valid.app = 2;
  // is_valid.misc = 1; // This expression is now invalidated.
  is_valid.platform = 1;

  ASSERT_EQ(is_valid.app, 2);
  ASSERT_EQ(is_valid.platform, 1);
}

TEST(scheduler_input_concepts, can_lack_multiple_data) {
  Concepts::SchedulerInput<Concepts::NoApplicationData, Concepts::NoPlatformData, int> is_valid;

  // is_valid.app = 2; // This expression is now invalidated.
  is_valid.misc = 1;
  // is_valid.platform = 1; // This expression is now invalidated.

  ASSERT_EQ(is_valid.misc, 1);
}

TEST(greedy_scheduler_requires, ntasks_funct) {
  Greedy::Scheduler<> greedy_scheduler;
}