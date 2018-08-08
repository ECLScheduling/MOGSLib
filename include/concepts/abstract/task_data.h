#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Concept)
  
/**
 * @brief A concept that displays methods to gather the data about the applications tasks.
 */
template <typename Concrete>
struct TaskData {
  static Concrete *concrete;

  /**
   * @brief Get the amount of tasks in the application.
   */
  static inline decltype(concrete->ntasks()) ntasks() {
    return concrete->ntasks();
  }

  /**
   * @brief Get the workloads of the tasks in the application.
   */
  static inline decltype(concrete->tasks_workloads()) tasks_workloads() {
    return concrete->tasks_workloads();
  }

};

template <typename Concrete>
Concrete* TaskData<Concrete>::concrete = nullptr;

END_NAMESPACE