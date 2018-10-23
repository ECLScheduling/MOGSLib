#pragma once

#include <system/static.h>

namespace MOGSLib { namespace Dependency {

/**
 * @brief the minimal dependency of a Scheduler.
 * @details A scheduler needs to at least know the amount of elements to schedule, hence the task_data variable.
 */
template<typename TaskData>
struct MinimalDependencies {
  TaskData *task_data;

  MinimalDependencies(std::tuple<TaskData*> concepts) : task_data(std::get<0>(concepts)) {}
};

}}