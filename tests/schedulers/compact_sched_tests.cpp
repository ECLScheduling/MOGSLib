#include <gtest/gtest.h>

#include "../type_definitions.h"
#include <schedulers/compact.h>

using Index = MOGSLib::Index;
using Load = MOGSLib::Load;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

struct DataDummyContainer {
  Index _ntasks;
  Index _nPEs;

  inline Index ntasks() {
    return _ntasks;
  }

  inline Index ntasks() const {
    return _ntasks;
  }

  inline Load* tasks_workloads() {
    return nullptr;
  }

  inline Index nPEs() const {
    return _nPEs;
  }

  inline Index nPEs() {
    return _nPEs;
  }

  inline Load* PEs_workloads() {
    return nullptr;
  }
};

using TestScheduler = MOGSLib::Scheduler::Compact<DataDummyContainer, DataDummyContainer>;

//TODO: This code is very similar to the greedy and roundrobin tests. Tests needs refactoring.
class CompactSchedTests : public ::testing::Test {
public:
  TestScheduler scheduler;
  DataDummyContainer data;
  TaskMap map;

  void setTask(const Index &ntasks) {
    data._ntasks = ntasks;
  }

  void setPE(const Index &nPEs) {
    data._nPEs = nPEs;
  }

  void execute_scheduler() {
    map = scheduler.work();
  }

  void SetUp() {
    data._ntasks = 0;
    data._nPEs = 0;

    scheduler.init(std::make_tuple(&data, &data));

    map = nullptr;
  }

  void TearDown() {
    if(map != nullptr) {
      delete [] map;
      map = nullptr;  
    }
    
  }
};

TEST_F(CompactSchedTests, single_task) {
  setTask(1);
  setPE(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
}

TEST_F(CompactSchedTests, two_tasks_two_PEs) {
  setTask(2);
  setPE(2);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);
}

TEST_F(CompactSchedTests, two_tasks_one_PE) {
  setTask(2);
  setPE(1);

  execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);
}

TEST_F(CompactSchedTests, n_tasks) {
  Index n = 6;
  Index nPEs = 2;
  
  setTask(n);
  setPE(nPEs);

  execute_scheduler();
  auto s = n/nPEs;
  for(Index j = 0; j < n/s; ++j)
    for(Index i = 0; i < s; ++i)
      ASSERT_EQ(j, map[j*s + i]);
}