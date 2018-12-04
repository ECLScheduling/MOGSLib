#include <gtest/gtest.h>

#include <type_definitions.h>
#include <schedulers/greedy.h>

using Index = MOGSLib::Index;
using Load = MOGSLib::Load;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

struct DataDummyContainer {
  Index _ntasks;
  Index _nPEs;

  Load *_tasks, *_PEs;

  DataDummyContainer() {
    _tasks = nullptr;
    _PEs = nullptr;
  }

  ~DataDummyContainer() {
    if(_tasks != nullptr) {
      delete [] _tasks;
      _tasks = nullptr;
    }
    if(_PEs != nullptr) {
      delete [] _PEs;
      _PEs = nullptr;
    }
  }

  inline Index ntasks() {
    return _ntasks;
  }

  inline Index ntasks() const {
    return _ntasks;
  }

  inline Load* tasks_workloads() {
    return _tasks;
  }

  inline Index nPEs() const {
    return _nPEs;
  }

  inline Index nPEs() {
    return _nPEs;
  }

  inline Load* PEs_workloads() {
    return _PEs;
  }
};

using TestScheduler = MOGSLib::Scheduler::Greedy<DataDummyContainer, DataDummyContainer>;

//TODO: This code is very similar to the roundrobin and compact tests. Tests needs refactoring.
class GreedySchedTests : public ::testing::Test {
public:
  TestScheduler scheduler;
  DataDummyContainer data;

  void setTask(const Index &ntasks) {
    data._ntasks = ntasks;
    data._tasks = new Load[ntasks]();
  }

  void setPE(const Index &nPEs) {
    data._nPEs = nPEs;
    data._PEs = new Load[nPEs]();
  }

  TaskMap execute_scheduler() {
    return scheduler.work();
  }

  void SetUp() {
    scheduler.init(std::make_tuple(&data, &data));
  }

  void TearDown() {
  }

};

TEST_F(GreedySchedTests, single_task) {
  setTask(1);
  setPE(1);

  auto map = execute_scheduler();
  ASSERT_EQ(0, map[0]);

  delete [] map;
}

TEST_F(GreedySchedTests, single_task_two_PEs) {
  setTask(1);
  setPE(2);

  data._PEs[0] = 20;
  data._PEs[1] = 10;

  auto map = execute_scheduler();

  ASSERT_EQ(1, map[0]);

  delete [] map;
}

TEST_F(GreedySchedTests, two_task_equally_loaded_PEs) {
  setTask(2);
  setPE(2);

  data._tasks[0] = 10;
  data._tasks[1] = 10;

  data._PEs[0] = 10;
  data._PEs[1] = 10;

  auto map = execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]);

  delete [] map;
}

TEST_F(GreedySchedTests, two_task_unequally_loaded_PEs) {
  setTask(2);
  setPE(2);

  data._tasks[0] = 10;
  data._tasks[1] = 10;

  data._PEs[0] = 0;
  data._PEs[1] = 30;

  auto map = execute_scheduler();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);

  delete [] map;
}

TEST_F(GreedySchedTests, three_task_unequally_loaded_PEs) {
  setTask(3);
  setPE(2);

  data._tasks[0] = 10;
  data._tasks[1] = 10;
  data._tasks[2] = 10;

  data._PEs[0] = 0;
  data._PEs[1] = 19;

  auto map = execute_scheduler();

  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,1,0)
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[0]);

  delete [] map;
}

TEST_F(GreedySchedTests, tasks_unequal_workload) {
  setTask(3);
  setPE(2);

  data._tasks[0] = 20;
  data._tasks[1] = 10;
  data._tasks[2] = 30;

  data._PEs[0] = 0;
  data._PEs[1] = 40;

  auto map = execute_scheduler();

  EXPECT_EQ(0, map[2]); // The make_heap modifies the ordering to (2,0,1)
  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(1, map[1]); 

  delete [] map;
}