#include <gtest/gtest.h>

#include <schedulers/round_robin.h>

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

using TestScheduler = MOGSLib::Scheduler::RoundRobin<DataDummyContainer, DataDummyContainer>;
using TaskData = typename TestScheduler::TaskData;
using PEData = typename TestScheduler::PEData;

class RoundRobinTests : public ::testing::Test {
public:
  TestScheduler scheduler;
  DataDummyContainer data;

  void setTask(const Index &ntasks) {
    data._ntasks = ntasks;
  }

  void setPE(const Index &nPEs) {
    data._nPEs = nPEs;
  }

  TaskMap execute_scheduler() {
    return scheduler.work();
  }

  void SetUp() {
    data._ntasks = 0;
    data._nPEs = 0;

    TaskData::concrete = &data;
    PEData::concrete = &data;
  }

  void TearDown() {
    TaskData::concrete = nullptr;
    PEData::concrete = nullptr;
  }

};

TEST_F(RoundRobinTests, single_task) {
  setTask(1);
  setPE(1);

  auto map = execute_scheduler();
  ASSERT_EQ(0, map[0]);

  delete [] map;
}

TEST_F(RoundRobinTests, two_tasks) {
  setTask(2);
  setPE(2);

  auto map = execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(1, map[1]);

  delete [] map;
}

TEST_F(RoundRobinTests, two_tasks_one_PE) {
  setTask(2);
  setPE(1);

  auto map = execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[1]);

  delete [] map;
}

TEST_F(RoundRobinTests, n_tasks) {
  auto n = 3;
  setTask(n);
  setPE(n-1);

  auto map = execute_scheduler();
  ASSERT_EQ(0, map[0]);
  ASSERT_EQ(0, map[n-1]);

  delete [] map;
}