#pragma once

#include <vector>

template<typename TaskType>
class SimplePE {
public:
  typedef TaskType Task;
  typedef Task::Id Id;
  typedef Task::Load Load;

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
  Load load;

public:

  /**
   * An unsafe constructor, but may be used to create static arrays.
   * @details It does not initialize the internal state.
   */
  SimplePE() {}

  /**
   * A safe constructor that initializes the internal state.
   * @param anId The task's id.
   */
  SimplePE(const Id &anId) {
    id = anId;
  }

  /**
   * This object does not allocate any pointers, it simply uses already existent pointers.
   */
  ~SimplePE() {}

  /**
   * A comparator that compares a simple task with other solely by the load value.
   */
  const bool operator>(const SimplePE &other) const {
    return load > other.load;
  }

  /**
   * Sets the load for this PE.
   * @details This implementation does like so because the method to calculate the PE can be different depending on the strategy.
   * @param aLoad A load value to the PE.
   */
  void setLoad(Load aLoad) {
    load = aLoad;
  }

  /**
   * @return The load of this PE.
   */
  const Load &load() {
    return load;
  }

  /**
   * A function to map a task in the PE.
   * @param task A pointer to the mapped task.
   */
  void mapTask(Task *task) {
    tasks.push_back(task);
  }

}