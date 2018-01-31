#pragma once

#include <vector>
#include <map>

/**
 * @brief This class serve as a form of output to the strategies in this library.
 */
template <typename Id>
class StrategyOutput {
public:

  /**
   * A map of PE ids to a collection of Task ids.
   */
  std::map<Id, std::vector<Id> > map;

  /**
   * Sets a task to a PE.
   * @param peId The id of the PE.
   * @param taskId The id of the task that will be mapped to the PE.
   */
  void set(const Id peId, const Id taskId) {
    auto it = map.find(peId);

    if(it != map.end())
      it->second.push_back(taskId);
    else
      map[peId] = std::vector<Id> {taskId};
  }

  /**
   * Sets multiple tasks to a PE.
   * @param peId The id of the PE.
   * @param tasks The vector of tasks to be mapped to the peId.
   */
  void setMultiple(const Id peId, const std::vector<Id> &tasks) {
    auto it = map.find(peId);

    if(it != map.end())
      it->second.insert(it->second.end(), tasks.begin(), tasks.end());
    else
      map[peId] = tasks;
  }

};