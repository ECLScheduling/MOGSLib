#pragma once

#include <policies/greedy.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @brief Class that represents a scheduler which utilizes a greedy heuristic to output a task map.
 **/
template<typename WorkloadTypes, template<typename ...T> typename InputT>
class Greedy {
public:
  using Input = InputT<typename WorkloadTypes::Index, typename WorkloadTypes::Load>;
  using InputTuple = std::tuple<Input&>;

  using Schedule = typename WorkloadTypes::Schedule;
  using Policy = MOGSLib::Policy::Greedy<WorkloadTypes>;

  /**
   *  @brief The method to obtain a task map based on a greedy heuristic.
   **/
  Schedule work(InputTuple input) override {
    auto data = std::get<0>(input);
    auto schedule = Schedule(data.ntasks());
    
    Policy::map(schedule, data.task_workloads(), data.pu_workloads());
    return map;
  }
};

}}
