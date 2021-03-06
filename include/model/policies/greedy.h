#pragma once

#include "dependencies/workload_aware.h"
#include <algorithm>

namespace MOGSLib { namespace Policy {

template<typename ... Deps>
class Greedy;

/**
 *  @class Greedy
 *  @tparam WorkloadTypes A specialized structure to define the necessary basic types for schedulers.
 *  @tparam Id An index type to organize PUs and tasks.
 *  @tparam L The type of load to be ordered. It has to be a numeric type.
 */
template<typename I, typename L>
struct Greedy<MOGSLib::Dependency::WorkloadAware<I,L>> {
  using Deps = MOGSLib::Dependency::WorkloadAware<I,L>;
  using Id = typename Deps::Id;
  using Load = typename Deps::Load;
  using Schedule = typename Deps::Schedule;

protected:
  /**
   *  @brief The type definition for a Comparator of type T.
   *  @tparam T The type to be compared.
   *  @tparam DecreasingOrder Whether or not the comparison will be used to sort in a decreasing order.
   */
  template<typename T, bool DecreasingOrder>
  using Compare = std::conditional_t<DecreasingOrder, std::less<T>, std::greater<T>>;

  /**
   *  @class Workload
   *  @brief An abstraction of a load anotated with an id.
   *
   *  The TaskMap of scheduler outputs must follow the same indexes as the output received by the scheduler.
   *  Therefore, this structure holds a reference to the original index of the load, being useful when the workload must be sorted.
   */
  struct Workload {
    Id id;
    Load load;
    
    /// @brief Constructs an empty Workload object.
    Workload() {}
    /// @brief Constructs a complete Workload object.
    Workload(const Id &i, const Load &l) : id(i), load(l) {}

    /// @brief Compares two instances of Workload based on their load value.
    inline bool operator >(const Workload &o) const { return load > o.load; }
    /// @brief Compares two instances of Workload based on their load value.
    inline bool operator <(const Workload &o) const { return load < o.load; }
  };

  /**
   *  @brief Creates a heap of Workload instances based on a vector of loads.
   *  @tparam DecreasingOrder this parameter is used to define if the constructed heap is a min-heap or a max-heap.
   *  @param loads A vector of load values.
   */
  template<bool DecreasingOrder>
  static inline std::vector<Workload> create_workload_heap(const std::vector<Load> &loads) {
    std::vector<Workload> v(loads.size());
    Id i = 0;
    std::transform(loads.begin(), loads.end(), v.begin(), [&i](auto load) { return Workload(i++, load); });
    std::make_heap(v.begin(), v.end(), Compare<Workload, DecreasingOrder>());
    return v;
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
  static void map(Schedule &map, const std::vector<Load> &task_loads, const std::vector<Load> &pu_loads) {
    auto tasks = create_workload_heap<true>(task_loads);
    auto pus = create_workload_heap<false>(pu_loads);
  
    while(!tasks.empty()) {
      auto &task = tasks.front();
      auto &pu = pus.front(); // heap-top (peek)

      map[task.id] = pu.id; // Set the output.
      pu.load += task.load; // Update the PE with the added task's load.

      std::pop_heap(tasks.begin(), tasks.end(), Compare<Workload, true>());
      tasks.pop_back();
      std::pop_heap(pus.begin(), pus.end(), Compare<Workload, false>());
      std::push_heap(pus.begin(), pus.end(), Compare<Workload, false>());
    }
  }

};

}}