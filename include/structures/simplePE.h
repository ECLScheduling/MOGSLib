#pragma once

#include <vector>

template<typename TaskType>
class SimplePE {
public:
  typedef TaskType Task;
  typedef typename Task::Id Id;
  typedef typename Task::Load Load;

  /**
   * The tasks this PE contains.
   */
  std::vector<Id> tasks;

protected:

  /**
   * The PE's load, which is safer to be protected since it must be calculated and set.
   */
  Load aLoad;

  /**
   * The PE's id.
   */
  Id anId;

public:

  /**
   * An unsafe constructor, but may be used to create static arrays.
   * @details It does not initialize the internal state.
   */
  SimplePE() {
    aLoad = 0;
  }

  /**
   * A safe constructor that initializes the internal state.
   * @param id The task's id.
   */
  SimplePE(const Id id) {
    aLoad = 0;
    anId = id;
  }

  /**
   * This object does not allocate any pointers, it simply uses already existent pointers.
   */
  ~SimplePE() {}

  /**
   * A less than comparator that compares a simple task with other solely by the load value.
   */
  inline const bool operator<(const SimplePE &other) const {
    return aLoad < other.aLoad;
  }

  /**
   * A greater than comparator that compares a simple task with other solely by the load value.
   */
  const bool operator>(const SimplePE &other) const {
    return aLoad > other.aLoad;
  }

  /**
   * Sets the load for this PE.
   * @details This implementation does like so because the method to calculate the PE can be different depending on the strategy.
   * @param load A load value to the PE.
   */
  inline void setLoad(const Load load) {
    aLoad = load;
  }

  /**
   * Sets the id for this PE.
   * @param id An id value for this PE.
   */
  inline void setId(const Id id) {
    anId = id;
  }

  /**
   * @return The load of this PE.
   */
  inline const Load &load() {
    return aLoad;
  }

  /**
   * @return The load of this PE.
   */
  inline const Id &id() {
    return anId;
  }

  /**
   * A function to map a task in the PE.
   * @param id The id of the mapped task.
   * @param load The load of the mapped task.
   */
  inline void map(const Id id, const Load load) {
    tasks.push_back(id);
    aLoad += load;
  }

  /**
   * @return The quantity of tasks mapped to this PE.
   */
  inline const unsigned int taskCount() const {
    return tasks.size();
  }

};