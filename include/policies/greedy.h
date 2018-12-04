#pragma once

#include <vector>
#include <algorithm>

namespace MOGSLib { namespace Policy {

/**
 *  @class Greedy
 *  @brief A workload aware policy that iteratively assigns the heavier load to the most underloaded processor.
 *  @tparam _Load The type of load to be ordered. It has to be a numeric type.
 */
template<typename _Load = MOGSLib::Load>
class Greedy {
protected:
  using Index = MOGSLib::Index;
  using TaskMap = MOGSLib::TaskMap;

  struct LoadContainer {
    _Load load;
    Index id;

    inline void operator =(const LoadContainer &t) {
      load = t.load;
      id = t.id;
    }

    inline bool operator >(const LoadContainer &t) const {
      return load > t.load;
    }

    inline bool operator <(const LoadContainer &t) const {
      return load < t.load;
    }
  };

  static inline bool maxCmp(const LoadContainer& a, const LoadContainer& b) {
    return a < b;
  }

  static inline bool minCmp(const LoadContainer& a, const LoadContainer& b) {
    return a > b;
  }

public:

  /**
   *  @brief map The map of task-to-pu that will serve as the output.
   *  @param tasks A vector of task workloads.
   *  @param pus A vector of pu workloads.
   *
   *  Sorts the tasks in a min heap and the pus in a max heap.
   *  Iteratively pops from the task heap and assign the task to the head ot the pu heap iteratively.
   */
  static void map(TaskMap &map, std::vector<Load> &tasks, std::vector<Load> &pus) {
    std::vector<LoadContainer> tasks(ntasks);
    std::vector<LoadContainer> PEs(nPEs);
  
    for(Index i = 0; i < tasks.size(); ++i) {
      tasks[i].load = task_loads[i];
      tasks[i].id = i;
    }

    for(Index i = 0; i < PEs.size(); ++i) {
      PEs[i].load = PE_loads[i];
      PEs[i].id = i;
    }
  
    std::make_heap(tasks.begin(), tasks.end(), Greedy::maxCmp);
    std::make_heap(PEs.begin(), PEs.end(), Greedy::minCmp);

    while(!tasks.empty()) {
      auto &task = tasks.front();
      auto &PE = PEs.front(); // heap-top (peek)

      map[task.id] = PE.id; // Set the output.
      PE.load += task.load; // Update the PE with the added task's load.

      std::pop_heap(tasks.begin(), tasks.end(), Greedy::maxCmp);
      tasks.pop_back();
      std::pop_heap(PEs.begin(), PEs.end(), Greedy::minCmp);
      std::push_heap(PEs.begin(), PEs.end(), Greedy::minCmp);
    }
  }

};

}}