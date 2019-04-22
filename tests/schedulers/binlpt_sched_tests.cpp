#include <gtest/gtest.h>

#include <model/schedulers/binlpt.h>

#include <sched_tests/workload_base.h>

class BinLPTSchedTests : public WorkloadSchedulerTests {
public:
  using Scheduler = MOGSLib::Scheduler::BinLPT<Context>;
  Scheduler scheduler;

  virtual Schedule call_scheduler(Context &c) {
    return scheduler.work(c);
  }
};


TEST_F(BinLPTSchedTests, policy_regular_tasks_unloaded_PUs) {
  pu_loads(2, LoadGenerator::regular<0>);
  k(2);
  task_loads(4, LoadGenerator::regular<5>); // [5,5,5,5] => 0:[5,5,5] 1:[5] => assign order:{0,1}

  execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(1, map[3]);
}

TEST_F(BinLPTSchedTests, policy_irregular_tasks_unloaded_PUs) {
  pu_loads(2, LoadGenerator::regular<0>);
  k(2);
  task_loads(5, LoadGenerator::increasing); // [1,2,3,4,5] => 0:[1,2,3,4] 1:[5] => assign order:{0,1}

  execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(0, map[3]);
  EXPECT_EQ(1, map[4]);
}

TEST_F(BinLPTSchedTests, policy_irregular_tasks_decreasing_unloaded_PUs) {
  pu_loads(2, LoadGenerator::regular<0>);
  k(4);
  task_loads(5, LoadGenerator::decreasing<5>); // [5,4,3,2,1] => mean = 3 (15/4) => 0:[5], 1:[4], 2:[3,2] 3:[1] => assign order:{0,2,1,3} 

  execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}

TEST_F(BinLPTSchedTests, policy_regular_tasks_loaded_PEs) {
  pu_loads(2, LoadGenerator::regular<0>);
  k(2);
  task_loads(4, LoadGenerator::regular<5>); // [5,5,5,5] => 0:[5,5,5] 1:[5] => ordered:{0,1}
  pu_at(0) = 7;

  execute_scheduler();

  EXPECT_EQ(1, map[0]);
  EXPECT_EQ(1, map[1]);
  EXPECT_EQ(1, map[2]);
  EXPECT_EQ(0, map[3]);
}

TEST_F(BinLPTSchedTests, policy_irregular_tasks_loaded_PEs) {
  pu_loads(4, LoadGenerator::regular<0>);
  k(3);
  task_loads(5, LoadGenerator::increasing); // [1,2,3,4,5] => 0:[1,2,3] 1:[4,5] 2:[] => ordered:{0,1}
  pu_at(0) = 7;

  execute_scheduler();

  EXPECT_EQ(2, map[0]);
  EXPECT_EQ(2, map[1]);
  EXPECT_EQ(2, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}