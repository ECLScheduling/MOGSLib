#pragma once

#include <system/type_definitions.h>
#include <vector>
#include <algorithm>

namespace Policy {

template<typename _Load = Load>
class Greedy {
protected:

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

  static void map(TaskMap &map, const Index &ntasks, _Load *task_loads, const Index &nPEs, const _Load *PE_loads) {
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

}