#include <gtest/gtest.h>

#include "../type_definitions.h"
#include <schedulers/binlpt.h>

#include <vector>

using Index = MOGSLib::Index;
using Load = MOGSLib::Load;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

struct DataDummyContainer {
  Index k;
  std::vector<Load> task_loads;
  std::vector<Load> PE_loads;

  inline Index ntasks() {
    return task_loads.size();
  }

  inline Index ntasks() const {
    return task_loads.size();
  }

  inline Load* tasks_workloads() {
    return task_loads.data();
  }

  inline Index nPEs() const {
    return PE_loads.size();
  }

  inline Index nPEs() {
    return PE_loads.size();
  }

  inline Load* PEs_workloads() {
    return PE_loads.data();
  }
};

using TestScheduler = MOGSLib::Scheduler::BinLPT<DataDummyContainer, DataDummyContainer, Index>;

class BinLPTSchedTests : public ::testing::Test {
public:
  TestScheduler scheduler;
  DataDummyContainer data;
  TaskMap map;

  void unloaded_PEs(const Index &nPEs) {
    for(Index i = 0; i < nPEs; ++i)
      data.PE_loads.push_back(0);
  }

  void regular_loads(const Index &n, const Load &wl) {
    for(Index i = 0; i < n; ++i)
      data.task_loads.push_back(wl);
  }

  void increasing_loads(const Index &n) {
    for(Index i = 0; i < n; ++i) {
      Load wl = i+1;
      data.task_loads.push_back(wl);
    }
  }

  void decreasing_loads(const Index &n) {
    for(Index i = 0; i < n; ++i) {
      Load wl = n-i;
      data.task_loads.push_back(wl);
    } 
  }

  void PE_workload_at_is(const Index &n, const Load &wl) {
    data.PE_loads[n] = wl;
  }

  void k_is(const Index &k) {
    data.k = k;
  }

  void execute_scheduler() {
    map = scheduler.work();
  }

  void SetUp() {
    data.k = 0;

    scheduler.init(std::make_tuple(&data, &data, &data.k));

    map = nullptr;
  }

  void TearDown() {
    if(map != nullptr) {
      delete [] map;
      map = nullptr;  
    }
  }
};


TEST_F(BinLPTSchedTests, policy_regular_tasks_unloaded_PEs) {
  unloaded_PEs(2);
  k_is(2);
  regular_loads(4, 5); // [5,5,5,5] => 0:[5,5] 1:[5,5] => assign order:{0,1}

  execute_scheduler();

  EXPECT_EQ(1, map[0]);
  EXPECT_EQ(1, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(0, map[3]);
}

TEST_F(BinLPTSchedTests, policy_irregular_tasks_unloaded_PEs) {
  unloaded_PEs(2);
  k_is(2);
  increasing_loads(5); // [1,2,3,4,5] => 0:[1,2,3,4] 1:[5] => assign order:{0,1}

  execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(0, map[3]);
  EXPECT_EQ(1, map[4]);
}

TEST_F(BinLPTSchedTests, policy_irregular_tasks_decreasing_unloaded_PEs) {
  unloaded_PEs(2);
  k_is(4);
  decreasing_loads(5); // [5,4,3,2,1] => 0:[5] 1:[4] 2:[3,2] 3:[1] => ordered:{0,2,1,3}

  execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}

TEST_F(BinLPTSchedTests, policy_regular_tasks_loaded_PEs) {
  unloaded_PEs(2);
  k_is(2);
  regular_loads(4, 5); // [5,5,5,5] => 0:[5,1] 1:[5,5] => ordered:{0,1}
  PE_workload_at_is(0, 7);

  execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[2]);
  EXPECT_EQ(1, map[3]);
}

TEST_F(BinLPTSchedTests, policy_irregular_tasks_loaded_PEs) {
  unloaded_PEs(4);
  k_is(3);
  increasing_loads(5); // [1,2,3,4,5] => 0:[1,2,3] 1:[4,5] 2:[] => ordered:{0,1}
  PE_workload_at_is(0, 7);

  execute_scheduler();

  EXPECT_EQ(2, map[0]);
  EXPECT_EQ(2, map[1]);
  EXPECT_EQ(2, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}