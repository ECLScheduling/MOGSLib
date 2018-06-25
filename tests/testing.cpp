#include <gtest/gtest.h>

#include <adaptors/task_data.h>
#include <adaptors/pe_data.h>
#include <policies/roundRobin/policy.h>

template<typename T>
using TaskData = Concepts::TaskData<T>;

template<typename T>
using PEData = Concepts::PEData<T>;

using RoundRobin = Policies::RoundRobin;

class DummyData {
public:

  int _ntasks;
  int _nPEs;

  int *_PEs_workloads;
  int *_tasks_workloads;

  DummyData(int ntasks, int nPEs) {
    _ntasks = ntasks;
    _nPEs = nPEs;

    _PEs_workloads = new int[nPEs]();
    _tasks_workloads = new int[ntasks]();
    for(auto i = 1; i < _ntasks; ++i)
      _tasks_workloads[i-1] = i;
  }

  ~DummyData() {
    delete [] _tasks_workloads;
    delete [] _PEs_workloads;
  }

  inline int ntasks() {
    return _ntasks;
  }

  inline int nPEs() {
    return _nPEs;
  }

  inline int* tasks_workloads() {
    return _tasks_workloads;
  }

  inline int* PEs_workloads() {
    return _PEs_workloads;
  }

};

TEST(task_data, ntasks) {
  DummyData dummy = DummyData(20, 4);

  TaskData<DummyData> taskData;
  PEData<DummyData> PEData;

  taskData.c = &dummy;
  PEData.c = &dummy;

  std::cout << "Number of tasks: " << taskData.ntasks() << std::endl;
  std::cout << "Number of PEs: " << PEData.nPEs() << std::endl;

  RoundRobin rr;
  RoundRobin::TaskMap map = new RoundRobin::TaskEntry[taskData.ntasks()];

  rr.map(map, taskData.ntasks(), PEData.nPEs());

  for(auto i = 0; i < taskData.ntasks(); ++i)
    std::cout << map[i] << std::endl;
}

