#include <gtest/gtest.h>

#include <schedulers/task_pack.h>

#include <sched_tests/minimal_base.h>

class TaskPackSchedTests : public BaseSchedulerTests {
public:
  using Scheduler = MOGSLib::Scheduler::TaskPack<Context>;
  Scheduler scheduler;

  virtual Schedule call_scheduler() {
    return scheduler.work();
  }

  void packs(const Id &n) {
    Context::_k = n;
  }

  void SetUp() {
    BaseSchedulerTests::SetUp();
  }
};

TEST_F(TaskPackSchedTests, single_task) {
  tasks(1);
  pus(1);
  packs(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
}

TEST_F(TaskPackSchedTests, single_task_two_packs) {
  tasks(1);
  pus(1);
  packs(2);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
}

TEST_F(TaskPackSchedTests, two_tasks_two_PEs_one_pack) {
  tasks(2);
  pus(2);
  packs(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

TEST_F(TaskPackSchedTests, two_tasks_two_PEs_two_pack) {
  tasks(2);
  pus(2);
  packs(2);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

TEST_F(TaskPackSchedTests, odd_tasks_even_packs) {
  tasks(5);
  pus(3);
  packs(3);

  execute_scheduler();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(2, map[4]);
}

TEST_F(TaskPackSchedTests, less_PEs_than_packs) {
  tasks(5);
  pus(2);
  packs(3);

  execute_scheduler();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(0, map[4]);
}

TEST_F(TaskPackSchedTests, more_PEs_than_packs) {
  tasks(5);
  pus(4);
  packs(2);

  execute_scheduler();
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}