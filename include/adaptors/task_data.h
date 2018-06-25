#pragma once

namespace Concepts {

/**
 * @brief A concept that displays methods to gather the data about the applications tasks.
 */
template<typename Concrete>
class TaskData {
public:
  Concrete *c;

  /**
   * @brief Get the amount of tasks in the application.
   */
  inline decltype(c->ntasks()) ntasks() {
    return c->ntasks();
  }

  /**
   * @brief Get the workloads of the tasks in the application.
   */
  inline decltype(c->tasks_workloads()) tasks_workloads() {
    return c->tasks_workloads();
  }

};

}