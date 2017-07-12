#pragma once

#include <vector>

template<typename TaskType>
class SimplePE {
public:
  typedef TaskType Task;
  typedef typename Task::Id Id;
  typedef typename Task::Load Load;

  /**
   * The PE's id.
   */
  Id id;

  /**
   * The tasks this PE contains.
   */
  std::vector<Task*> tasks;

protected:

  /**
   * The PE's load, which is safer to be protected since it must be calculated and set.
   */
  Load _load;

public:

  /**
   * An unsafe constructor, but may be used to create static arrays.
   * @details It does not initialize the internal state.
   */
  SimplePE() {
    _load = 0;
  }

  /**
   * A safe constructor that initializes the internal state.
   * @param anId The task's id.
   */
  SimplePE(const Id &anId) {
    _load = 0;
    id = anId;
  }

  /**
   * This object does not allocate any pointers, it simply uses already existent pointers.
   */
  ~SimplePE() {}

  /**
   * A less than comparator that compares a simple task with other solely by the load value.
   */
  const bool operator<(const SimplePE &other) const {
    return _load < other._load;
  }

  /**
   * A greater than comparator that compares a simple task with other solely by the load value.
   */
  const bool operator>(const SimplePE &other) const {
    return _load > other._load;
  }

  /**
   * Sets the load for this PE.
   * @details This implementation does like so because the method to calculate the PE can be different depending on the strategy.
   * @param aLoad A load value to the PE.
   */
  void setLoad(Load aLoad) {
    _load = aLoad;
  }

  /**
   * @return The load of this PE.
   */
  const Load &load() {
    return _load;
  }

  /**
   * A function to map a task in the PE.
   * @param task A pointer to the mapped task.
   */
  void mapTask(Task *task) {
    tasks.push_back(task);
  }

  /**
   * @return The quantity of tasks mapped to this PE.
   */
  const unsigned int taskCount() const {
    return tasks.size();
  }

};