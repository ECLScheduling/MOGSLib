#include <gtest/gtest.h>

#include <model/schedulers/compact.h>

#include <sched_tests/minimal_base.h>

class CompactSchedTests : public BaseSchedulerTests {
public:
  using Scheduler = MOGSLib::Scheduler::Compact<Context>;
  Scheduler scheduler;

  virtual Schedule call_scheduler(Context &c) {
    return scheduler.work(c);
  }

  void SetUp() {
    BaseSchedulerTests::SetUp();
  }
};

TEST_F(CompactSchedTests, single_task) {
  tasks(1);
  pus(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
}

TEST_F(CompactSchedTests, two_tasks_two_PEs) {
  tasks(2);
  pus(2);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

TEST_F(CompactSchedTests, two_tasks_one_PE) {
  tasks(2);
  pus(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

TEST_F(CompactSchedTests, tasks) {
  Id n = 6;
  Id nPEs = 2;
  
  tasks(n);
  pus(nPEs);

  execute_scheduler();
  auto s = n/nPEs;
  for(Id j = 0; j < n/s; ++j)
    for(Id i = 0; i < s; ++i)
      ASSERT_EQ(j, map[j*s + i]);
}