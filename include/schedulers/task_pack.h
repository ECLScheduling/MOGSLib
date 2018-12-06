#pragma once

#include <policies/task_pack.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename PolicyTypes, template<typename ...T> typename InputT, template<typename ...T> typename PacksT>
class TaskPack {
public:
  using Input = InputT<typename PolicyTypes::Index>;
  using Packs = PacksT<typename PolicyTypes::Index>;
  using InputTuple = std::tuple<Input&, Packs&>;

  using Schedule = typename PolicyTypes::Schedule;
  using Policy = MOGSLib::Policy::TaskPack<PolicyTypes>;

  /**
   *  @brief The method to obtain a task map based on a compact policy.
   **/
  Schedule work(InputTuple input) override {
    auto data = std::get<0>(input);
    auto packs = std::get<1>(input);

    auto schedule = Schedule(data.ntasks());
    Policy::map(schedule, data.ntasks(), data.npus(), packs.value);
    return map;
  }

};

}}