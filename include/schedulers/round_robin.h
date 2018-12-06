#pragma once

#include <policies/round_robin.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @brief Class that represents a scheduler which utilizes a round robin heuristic to output a task map.
 **/
template<typename PolicyTypes, template<typename ...T> typename InputT>
class RoundRobin {
public:
  using Input = InputT<typename PolicyTypes::Index>;
  using InputTuple = std::tuple<Input&>;

  using Schedule = typename PolicyTypes::Schedule;
  using Policy = MOGSLib::Policy::RoundRobin<PolicyTypes>;
  
  /**
   *  @brief The method to obtain a task map based on a roundrobin heuristic.
   **/
  Schedule work(InputTuple input) override {
    auto data = std::get<0>(input);

    auto schedule = Schedule(data.ntasks());
    Policy::map(schedule, data.ntasks(), data.npus());
    return map;
  }

};

}}