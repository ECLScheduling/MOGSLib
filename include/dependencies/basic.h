#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Dependency)

/**
 * @brief the minimal dependency of a Scheduler.
 * @details A scheduler needs to at least know the amount of elements to schedule, hence the task_data variable.
 */
template<typename TaskData>
struct BasicDependencies {
  TaskData *task_data;

  BasicDependencies(std::tuple<TaskData*> t) : task_data(std::get<0>(t)) {}
};

END_NAMESPACE