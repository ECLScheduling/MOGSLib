#pragma once

#include <vector>
#include <system/traits.h>

namespace EagerMap {

/**
 * A class that serve as a collection of task groups. An instance of this class may represent a task, a group of tasks, a group of group of tasks and so on.
 */
class TaskGroup {
public:
  typedef EagerMapTraits::Id Id; 
  typedef EagerMapTraits::UInt UInt;
  typedef std::vector<TaskGroup *> ElementGroup; 

  /**
   * Id of the groupable element.
   */
  Id id;

private:
  /**
   * A pointer to the set of elements this group contains, which can be single tasks or group of tasks or group of groups of tasks and so on.
   */
  ElementGroup _elements;

public:

  /**
   * Creates a group initializing all the needed variables but the pointer to the elements of the group.
   * @param anId The id of the group. If the group is a task
   */
  TaskGroup(const Id &anId = 0) : id(anId) {}

  /**
   * This class' destructor removes all the children groups and it's own allocated memory.
   */
  virtual ~TaskGroup() {
    while(nElements() > 0) {
      auto childTask = _elements.back();
      _elements.pop_back();
      delete childTask;
    }
  }

  /**
   * This method is used to set the list of elements of this group.
   * @defails This method is useful if there are elements that are in adjacent memory spaces, since this object actually sotores it's memory addresses.
   * @param elements The list of elements that compound this group.
   */
  virtual void setElements(TaskGroup * const elements, const UInt &size) {
    for(UInt i = 0; i < size; ++i)
      _elements.push_back(&elements[i]);
  }

  /**
   * Stores a pointer to an element into the array of elements that this group is compound of.
   * @param element A pointer to the element.
   */
  virtual void setElement(TaskGroup * const element) {
    _elements.push_back(element); 
  }

  /**
   * Gets a reference to the element in a given index.
   * @details This method will always fail for a Task, which is a special case of group, since it has no child elements.
   * @param index The index which the element will be retrieved.
   */
  TaskGroup* const elementAt(const UInt &index) {
    assert(index < _elements.size());
    return _elements[index];
  }

  /**
   * Gets the number of elements in this group.
   */
  virtual const UInt nElements() const {
    return _elements.size();
  }

};

}