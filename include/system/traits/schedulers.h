#pragma once

#include <system/types.h>

#include <dependencies/workload_aware.h>

namespace MOGSLib {

/**
 * @brief This template structures are meant to be used to hold static data about the schedulers.
 * @details The only required trait to be informed in these structures is the name of the scheduler. This is meant to be able to chose the scheduler during runtime.
 */
template<Abstraction::SchedulerEnum T>
struct SchedulerTraits {
  static std::string name() { return "null"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::BasicDependencies<Concepts...>;
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::round_robin> {
  static std::string name() { return "roundrobin"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAware<Concepts...>;
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::compact> {
  static std::string name() { return "compact"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAware<Concepts...>;
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::task_pack> {
  static std::string name() { return "taskpack"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAwareWithK<Concepts...>;
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::greedy> {
  static std::string name() { return "greedy"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAware<Concepts...>;
};

template<>
struct SchedulerTraits<Abstraction::SchedulerEnum::binlpt> {
  static std::string name() { return "binlpt"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAwareWithK<Concepts...>;
};

}