#pragma once

#include <lb/loadBalancer.h>
#include <lb/input/basicInput.h>
#include <queue>
#include <iostream>

/**
 * Template class used to generate a static type-error when the GreedyLB tries to be used with a class that is not child of it's input requires.
 */
template<typename InputType, bool = std::is_base_of<BasicInput, InputType>::value>
class GreedyLB : public LoadBalancer<InputType> {
  static_assert(std::is_base_of<BasicInput, InputType>::value, "The GreedyLB 'InputType' must inherit from the baseclass 'BasicInput'.");
};

/**
 * Class that implements a greedy trategy to load balancing using the most basic form of input.
 */
template<typename InputType>
class GreedyLB<InputType, true> : public LoadBalancer<InputType> {
public:
  typedef BasicInput::Id Id;
  typedef BasicInput::Load Load;

  /**
   * Internal Helper instruction to decribe both PEs and Tasks by their ids and current load.
   * @variable id The id of the task or PE.
   * @variable load The load of the task or PE.
   */
  struct LoadBearer {
    Id id;
    Load load;

    LoadBearer(const Id &anId, const Load &aLoad) : id(anId), load(aLoad) {}
  };

  /**
   * Internal Helper struct to be used as the max-heap comparator.
   */
  struct MaxHeapComparator {
    inline bool operator ()(const LoadBearer &a, const LoadBearer &b) const {
      return a.load < b.load;
    }
  };

  /**
   * Internal Helper struct to be used as the min-heap comparator.
   */
  struct MinHeapComparator {
    inline bool operator ()(const LoadBearer &a, const LoadBearer &b) const {
      return a.load > b.load;
    }
  };

  typedef std::priority_queue<LoadBearer, std::vector<LoadBearer>, MaxHeapComparator > MaxHeap;
  typedef std::priority_queue<LoadBearer, std::vector<LoadBearer>, MinHeapComparator > MinHeap;

  /**
   * @variable PEs The min-heap of PEs used in the greedy strategy.
   */
  MinHeap PEs;

  /**
   * @variable Tasks The max-heap of Tasks used in the greedy strategy.
   */
  MaxHeap tasks;

  /**
   * This function populates the PEs heap with the ids of the processors and their load is set to 0.
   * @param input The input reference which was passed to the GreedyLB.
   */
  inline void createPEHeap(const InputType &input) {
    auto peIdSet = input.getPEsIds();

    PEs = MinHeap();
    for(auto it = peIdSet.begin(); it != peIdSet.end(); ++it)
      PEs.push(LoadBearer(*it,0));
  }

  /**
   * This function populates the Tasks heap with the ids and loads of the input's tasks.
   * @param input The input reference which was pased to the GreedyLB.
   */
  inline void createTaskHeap(const InputType &input) {
    auto taskIdSet = input.getTasksIds();

    tasks = MaxHeap();
    for(auto it = taskIdSet.begin(); it != taskIdSet.end(); ++it)
      tasks.push(LoadBearer(*it, input.getTaskLoad(*it)));
  }

  /**
   * The bootstrap function which will start the strategy's implementation.
   */
  void doWork(const InputType &input) {
    createPEHeap(input);
    createTaskHeap(input);

    if(PEs.empty())
      return;

    while(!tasks.empty()) {
      const LoadBearer task = tasks.top();
      const LoadBearer PE = PEs.top();

      tasks.pop();
      PEs.pop();

      PEs.push(LoadBearer(PE.id, PE.load + task.load));

      this->lbOutput.set(task.id, PE.id);
    }
  }

};

