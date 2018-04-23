#pragma once

#include <system/traits.h>
#include <vector>

namespace EagerMap {

using UInt = Traits<DefaultTypes>::UInt;

/**
 * @brief A structure used to create a group of tasks or group of group of tasks and so on.
 * @details This structure holds reference to all the underlying tasks that the group contains while at the same time providing easy access to group ids in the EagerMap algorithm.
 */
template<typename IndexType>
struct EagerGroup {
  using Wrapper = std::vector<IndexType>;
  Wrapper tasks;
  Wrapper members;

  EagerGroup() {}

  EagerGroup(const UInt &size) : members(Wrapper(size)) {}

  /**
   * @brief Create an array of <size> groups that represents one task each.
   */
  static inline EagerGroup* create_unitary_groups(const IndexType &size) {
    auto groups = new EagerGroup[size];
    for(IndexType i = 0; i < size; ++i){
      groups[i].members.push_back(i);
      groups[i].tasks.push_back(i);
    }
    return groups;
  }

  /**
   * @brief Register an element to a group and creates a reference for all the tasks wrapped in it.
   * @details This method expects that the size of the wrapper structure has alrready been set and filled with dummy values.
   */
  void register_element(const UInt &winner, const UInt &pos, bool *chosen, EagerGroup *previous_groups) {
    chosen[winner] = true;
    members[pos] = winner;
    for(auto task : previous_groups[winner].tasks)
      tasks.push_back(task);
  }
};

}