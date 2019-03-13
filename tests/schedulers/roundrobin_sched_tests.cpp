#include <gtest/gtest.h>

#include <schedulers/round_robin.h>

#include <sched_tests/minimal_base.h>

class RoundRobinSchedTests : public BaseSchedulerTests {
public:
  using Scheduler = MOGSLib::Scheduler::RoundRobin<Context>;
  Scheduler scheduler;

  virtual Schedule call_scheduler() {
    return scheduler.work();
  }

  void SetUp() {
    BaseSchedulerTests::SetUp();
  }
};

TEST_F(RoundRobinSchedTests, single_task) {
  tasks(1);
  pus(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
}

TEST_F(RoundRobinSchedTests, two_tasks) {
  tasks(2);
  pus(2);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

TEST_F(RoundRobinSchedTests, two_tasks_one_PE) {
  tasks(2);
  pus(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

TEST_F(RoundRobinSchedTests, tasks) {
  auto n = 3;
  tasks(n);
  pus(n-1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[n-1]);
}