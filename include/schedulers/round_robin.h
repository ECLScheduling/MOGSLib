#pragma once

#include <abstractions/scheduler.h>

#include <policies/round_robin.h>

#include <concepts/pe_data.h>
#include <concepts/task_data.h>

namespace Scheduler {

/**
 * @brief Class that represents a scheduler which utilizes a round robin heuristic to output a task map.
 **/
template<typename T, typename P = T>
class RoundRobin : public Abstraction::Scheduler {
public:
  using TaskData = Concepts::TaskData<T>;
  using PEData = Concepts::PEData<P>;

  RoundRobin() : Scheduler("roundrobin") {}

  /**
   * @brief The method to obtain a task map based on a roundrobin heuristic.
   **/
  TaskMap work() override {
    auto ntasks = TaskData::ntasks();
    auto nPEs = PEData::nPEs();

    auto map = new Index[ntasks]();
    Policy::RoundRobin::map(map, ntasks, nPEs);
    return map;
  }

};

}

/**
 * @brief This Bind specialization binds the concrete adapters T and P, required by the RounRobin scheduler, to their respective concepts, TaskData and PEData.
 */
template<typename T, typename P>
struct Bind<Scheduler::RoundRobin<T,P> > {
  static void bind(T* t, P *p) {
    Scheduler::RoundRobin<T,P>::TaskData::concrete = t;
    Scheduler::RoundRobin<T,P>::PEData::concrete = p;
  }
};