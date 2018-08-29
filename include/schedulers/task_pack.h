#pragma once

#include <abstractions/scheduler.h>
#include <policies/task_pack.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename ... _Concepts>
class TaskPack : public Abstraction::Scheduler<Abstraction::SchedulerEnum::task_pack> {
public:

  using Concepts = typename MOGSLib::SchedulerTraits<Abstraction::SchedulerEnum::task_pack>::Dependencies<_Concepts...>;
  std::unique_ptr<Concepts> concepts;

  /**
   * @brief The method that will initialize the references to the concrete concepts used by the scheduler.
   */
  void init(std::tuple<Concepts *...> ref) {
    concepts = std::make_unique<Concepts>(ref);
  }

  /**
   * @brief The method to obtain a task map based on a compact policy.
   **/
  TaskMap work() override {
    auto ntasks = concepts->task_data->ntasks();
    auto nPEs = concepts->PE_data->nPEs();
    auto npacks = concepts->k_data->k();

    auto map = new Index[ntasks]();
    Policy::TaskPack::map(map, ntasks, nPEs, npacks);
    return map;
  }

};

END_NAMESPACE