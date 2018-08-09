#pragma once

#include <system/types.h>

namespace MOGSLib {

/**
 * @brief This template structures are meant to be used to hold static data about the schedulers.
 * @details The only required trait to be informed in these structures is the name of the scheduler. This is meant to be able to chose the scheduler during runtime.
 */
template<Abstraction::SchedulerEnum T>
struct SchedulerTraits {
  static constexpr auto name = "null";
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::round_robin> {
  static constexpr auto name = "roundrobin";
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::compact> {
  static constexpr auto name = "compact";
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::task_pack> {
  static constexpr auto name = "taskpack";
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::greedy> {
  static constexpr auto name = "greedy";
};

}