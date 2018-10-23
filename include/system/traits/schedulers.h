#pragma once

#include <system/types.h>

#include <dependencies/workload_aware.h>

namespace MOGSLib {

/**
 * @brief This template structures are meant to be used to hold static data about the schedulers.
 * @details The only required trait to be informed in these structures is the name of the scheduler. This is meant to be able to chose the scheduler during runtime.
 */
template<SchedulerEnum T>
struct SchedulerTraits {
  static std::string name() { return "unimplemented"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::MinimalDependencies<Concepts...>;
};

template<>
struct SchedulerTraits<SchedulerEnum::round_robin> {
  static std::string name() { return "roundrobin"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAware<Concepts...>;
};

template<>
struct SchedulerTraits<SchedulerEnum::compact> {
  static std::string name() { return "compact"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAware<Concepts...>;
};

template<>
struct SchedulerTraits<SchedulerEnum::task_pack> {
  static std::string name() { return "taskpack"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAwareWithK<Concepts...>;
};

template<>
struct SchedulerTraits<SchedulerEnum::greedy> {
  static std::string name() { return "greedy"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAware<Concepts...>;
};

template<>
struct SchedulerTraits<SchedulerEnum::binlpt> {
  static std::string name() { return "binlpt"; }

  template<typename ... Concepts>
  using Dependencies = Dependency::WorkloadAwareWithK<Concepts...>;
};

}