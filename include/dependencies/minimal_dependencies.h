#pragma once

#include <tuple>

namespace MOGSLib { namespace Dependency {

/**
 * \brief the minimal dependency of a Scheduler.
 * @details A scheduler needs to at least know the amount of elements to schedule, hence the task_data variable.
 */
template<typename Types, template<typename ...T> typename InputT, typename T...>
struct MinimalDependency {
  using Input = InputT<typename Types::Index, ...T>;
  using Schedule = typename Types::Schedule;

  template<typename ... Others>
  using Dependencies = std::tuple<Input&, Others...>;
};

template<typename Types, template<typename ...T> typename InputT, typename T...>
struct WorkloadDependency {
  using Input = InputT<typename Types::Index, typename Types::Load, ...T>;
  using Schedule = typename Types::Schedule;

  template<typename ... Others>
  using Dependencies = std::tuple<Input&, Others...>;
};

}}