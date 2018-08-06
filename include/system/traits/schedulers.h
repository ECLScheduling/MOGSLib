#pragma once

#include <system/types.h>

namespace MOGSLib {

/**
 * @brief This template structures are meant to be used to hold static data about the schedulers.
 * @details The only required trait to be informed in these structures is the name of the scheduler. This is meant to be able to chose the scheduler during runtime.
 */
template<Abstractions::SchedulerEnum T>
struct SchedulerTraits {
  static constexpr auto name = "null";
};

template<>
struct SchedulerTraits<Abstractions::SchedulerEnum::round_robin> {
  static constexpr auto name = "roundrobin";
};

template<>
struct SchedulerTraits<Abstractions::SchedulerEnum::compact> {
  static constexpr auto name = "compact";
};

template<>
struct SchedulerTraits<Abstractions::SchedulerEnum::task_pack> {
  static constexpr auto name = "taskpack";
};

template<>
struct SchedulerTraits<Abstractions::SchedulerEnum::greedy> {
  static constexpr auto name = "greedy";
};

}