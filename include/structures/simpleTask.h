#pragma once

/**
 * A class that is an abstraction to a task in a parallel system. The simple task contains only a load and an id associated to it.
 */
template<typename IdType, typename LoadType>
class SimpleTask {
public:
  typedef IdType Id;
  typedef LoadType Load;


protected:

  /**
   * The id of the task.
   */
  Id anId;

  /**
   * The load of the task.
   */
  Load aLoad;

public:

  /**
   * An unsafe constructor, but may be used to create static arrays.
   * @details It does not initialize the internal state.
   */
  SimpleTask() {}

  /**
   * An copy constructor, useful for making copies of an object.
   */
  SimpleTask(const SimpleTask<IdType, LoadType> &copy) {
    anId = copy.anId;
    aLoad = copy.aLoad;
  }

  /**
   * A safe constructor that initializes the internal state.
   * @param id The task's id.
   * @param load The task's load.
   */
  SimpleTask(const Id &id, const Load &load) {
    anId = id;
    aLoad = load;
  }

  /**
   * This method sets the id of this task.
   * @param id The new id of the task.
   */
  inline void setId(const Id &id) {
    anId = id;
  }

  /**
   * This method sets the load of this task.
   * @param load The new load of the task.
   */
  inline void setLoad(const Load &load) {
    aLoad = load;
  }

  /**
   * This method returns the id of this task.
   */
  inline const Id &id() const {
    return anId;
  }

  /**
   * This method returns the load of this task.
   */
  inline const Load &load() const {
    return aLoad;
  }

  /**
   * A less comparator that compares a simple task with other solely by the load value.
   */
  const bool operator<(const SimpleTask &other) const {
    return aLoad < other.aLoad;
  }

  /**
   * A greater than comparator that compares a simple task with other solely by the load value.
   */
  const bool operator>(const SimpleTask &other) const {
    return aLoad > other.aLoad;
  }

};