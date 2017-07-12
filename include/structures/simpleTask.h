#pragma once

/**
 * A class that is an abstraction to a task in a parallel system. The simple task contains only a load and an id associated to it.
 */
template<typename IdType, typename LoadType>
class SimpleTask {
public:
  typedef IdType Id;
  typedef LoadType Load;

  /**
   * The id of the task.
   */
  Id id;

  /**
   * The load of the task.
   */
  Load load;

  /**
   * An unsafe constructor, but may be used to create static arrays.
   * @details It does not initialize the internal state.
   */
  SimpleTask() {}

  /**
   * An copy constructor, useful for making copies of an object.
   */
  SimpleTask(const SimpleTask<IdType, LoadType> &copy) {
    id = copy.id;
    load = copy.load;
  }

  /**
   * A safe constructor that initializes the internal state.
   * @param anId The task's id.
   * @param aLoad The task's load.
   */
  SimpleTask(const Id &anId, const Load &aLoad) {
    id = anId;
    load = aLoad;
  }

  /**
   * A less comparator that compares a simple task with other solely by the load value.
   */
  const bool operator<(const SimpleTask &other) const {
    return load < other.load;
  }

  /**
   * A greater than comparator that compares a simple task with other solely by the load value.
   */
  const bool operator>(const SimpleTask &other) const {
    return load > other.load;
  }

};