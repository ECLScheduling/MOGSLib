#pragma once

#include <abstractions/scheduler.h>
#include <policies/round_robin.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes a round robin heuristic to output a task map.
 **/
template<typename ... _Concepts>
class RoundRobin : public Abstraction::Scheduler<Abstraction::SchedulerEnum::round_robin> {
public:

  using Concepts = typename MOGSLib::SchedulerTraits<SchedulerType>::Dependencies<_Concepts...>;
  std::unique_ptr<Concepts> concepts;

  /**
   * @brief The method that will initialize the references to the concrete concepts used by the scheduler.
   */
  void init(std::tuple<Concepts *...> ref) {
    concepts = std::make_unique<Concepts>(ref);
  }

  /**
   * @brief The method to obtain a task map based on a roundrobin heuristic.
   **/
  TaskMap work() override {
    auto ntasks = concepts->task_data->ntasks();
    auto nPEs = concepts->PE_data->nPEs();

    auto map = new Index[ntasks]();
    Policy::RoundRobin::map(map, ntasks, nPEs);
    return map;
  }

};

END_NAMESPACE