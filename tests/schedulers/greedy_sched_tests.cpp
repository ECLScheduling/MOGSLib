#include <gtest/gtest.h>

#include <model/schedulers/greedy.h>
#include <sched_tests/workload_base.h>

class GreedySchedTests : public WorkloadSchedulerTests {
public:
  using Scheduler = MOGSLib::Scheduler::Greedy<Context>;
  Scheduler scheduler;

  virtual Schedule call_scheduler(Context &c) {
    return scheduler.work(c);
  }
};

TEST_F(GreedySchedTests, single_task) {
  tasks(1);
  pus(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
}

TEST_F(GreedySchedTests, single_task_two_PEs) {
  tasks(1);
  pus(2);

  pu_at(0) = 20;
  pu_at(1) = 10;

  execute_scheduler();

  ASSERT_EQ(1, map[0]);
}

TEST_F(GreedySchedTests, two_task_equally_loaded_PEs) {
  tasks(2);
  pus(2);

  task_at(0) = 10;
  task_at(1) = 10;

  pu_at(0) = 10;
  pu_at(1) = 10;

  execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]);
}

TEST_F(GreedySchedTests, two_task_unequally_loaded_PEs) {
  tasks(2);
  pus(2);

  task_at(0) = 10;
  task_at(1) = 10;

  pu_at(0) = 0;
  pu_at(1) = 30;

  execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
}

TEST_F(GreedySchedTests, three_task_unequally_loaded_PEs) {
  tasks(3);
  pus(2);

  task_at(0) = 10;
  task_at(1) = 10;
  task_at(2) = 10;

  pu_at(0) = 0;
  pu_at(1) = 19;

  execute_scheduler();

  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,1,0)
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[0]);
}

TEST_F(GreedySchedTests, tasks_unequal_workload) {
  tasks(3);
  pus(2);

  task_at(0) = 20;
  task_at(1) = 10;
  task_at(2) = 30;

  pu_at(0) = 0;
  pu_at(1) = 40;

  execute_scheduler();

  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,0,1)
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]); 
}