#pragma once

#include <gtest/gtest.h>
#include <queue>

typedef Traits<void>::Load Load;

const Load noPenalityFunction(unsigned int size) {
  return 0;
}

const Load linearPenalityFunction(unsigned int size) {
  return size;
}

const Load squarePenalityFunction(unsigned int size) {
  return size*size;
}

/**
 * Fixture for testing the GreedyPGStrategy strategy.
 */
template<typename GreedyPGStrategyType>
class GreedyPGStrategyFixture : public ::testing::Test {
public:
  typedef MinimalParallelInput Input;
  typedef Input::PE PE;
  typedef Input::Task Task;

  struct TaskPtrComparator {

    const bool operator()(Task *a, Task *b) {
      return *a < *b;
    }
  };

  GreedyPGStrategyType *strategy;
  
  unsigned int PECount, taskCount;
  const Load (*penalityFunction)(unsigned int);

  PE *PEs;
  Task *tasks;
  MinimalParallelInput *input;

  void SetUp() {
    penalityFunction = noPenalityFunction;
  }

  virtual void createStrategy() = 0;

  void TearDown() {
    delete strategy;
    delete input;
  }

  void createInput() {
    createPEs(PECount);
    input = new Input(PEs, tasks, PECount, taskCount);
  }

  const MigrationElement &mapTasks() {
    return strategy->mapTasks(*input);  
  }

  void createPEs(unsigned int N) {
    if(N == 0) {
      return;
    }

    PEs = new PE[N];
    for(unsigned int i = 0; i < N; ++i)
      PEs[i] = PE(i);
  }

  void createTasksWithIncrementalLoad() {
    tasks = new Task[taskCount];

    for(unsigned int i = 0; i < taskCount; ++i) {
      tasks[i] = Task(i, i);
    }
  }

  void createTasksWithDecrementingLoad() {
    tasks = new Task[taskCount];

    for(unsigned int i = 0; i < taskCount; ++i) {
      tasks[i] = Task(i, taskCount-i);
    }
  }

  void compareOutput(std::vector< std::vector<Load> > &expectedLoads, const std::vector<PE*> &mappedPEs) {
    for(unsigned int i = 0; i < PECount; ++i) {
      std::priority_queue<Task*, std::vector<Task*>, TaskPtrComparator> taskQueue;

      ASSERT_EQ(expectedLoads[i].size(), mappedPEs[i]->taskCount()) << "Failed at the " << i << " PE.";

      for(unsigned int j = 0; j < mappedPEs[i]->taskCount(); ++j) {
        taskQueue.push(mappedPEs[i]->tasks[j]);
      }
      for(unsigned int j = 0; j < mappedPEs[i]->taskCount(); ++j) {
        auto task = taskQueue.top();
        taskQueue.pop();
        ASSERT_EQ(expectedLoads[i][j], task->load) << "Failed at the " << i << " PE on the " << j+1 << "th task of the total " << mappedPEs[i]->taskCount() << ".";
      }
   }
 }
 
};