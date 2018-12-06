#pragma once

#include <policies/binlpt.h>

namespace MOGSLib { namespace Scheduler {

/**
 *  @class BinLPT
 *  @brief A scheduler which utilizes the binlpt policy to output a workload-aware task map.
 **/
template<typename WorkloadTypes, template<typename ...T> typename InputT, template<typename I> typename ChunksT>
class BinLPT {
public:
  using Input = InputT<typename WorkloadTypes::Index, typename WorkloadTypes::Load>;
  using Chunks = ChunksT<typename WorkloadTypes::Index>;
  using InputTuple = std::tuple<Input&, Chunks&>;

  using Schedule = typename WorkloadTypes::Schedule;
  using Policy = MOGSLib::Policy::BinLPT<WorkloadTypes>;
  
  /// @brief The method to obtain a schedule based on a binlpt policy.
  Schedule work(InputTuple input) override {
    auto data = std::get<0>(input);
    auto chunks = std::get<1>(input);
    auto schedule = Schedule(data.ntasks());
    
    Policy::map(schedule, data.task_workloads(), data.pu_workloads(), chunks.value);
    return schedule;
  }

};

}}