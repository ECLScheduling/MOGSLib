#pragma once

#include <system/debug.h>

#include "structures/sparseCommMatrix.h"
#include "structures/eagerGroup.h"

namespace EagerMap {

/**
 * @brief The struct that defines the generic EagerMap scheduler algorithms.
 *
 * @type Load A type that serve as a load abstraction to the algorithms.
 * @type UInt A type that serve as an unsigned integer to the algorithms.
 */
template<typename Load>
struct Algorithms {
  using IndexType = UInt;
  using CommVal = UInt;
  using CommMatrix = CommunicationSparseMatrix<IndexType,CommVal>;
  using Group = EagerGroup<IndexType>;

  /**
   * @brief Generates a group of tasks based on communication affinity.
   * @param comm The communication matrix.
   * @param total_elements The total amount of elements (rows) in the matrix.
   * @param group_elements The wanted size of the generated group.
   * @param chosen a boolean array to mark the chosen elements for a group to avoid selecting the same element twice.
   * @param previous_groups The array containing the groups of previous iterations.
   */
  static Group* generate_groups(CommMatrix &comm, UInt total_elements, UInt group_elements, bool *chosen, Group *previous_groups);

  /**
   * @brief Recreate the communication matrix based on the new groups communication patterns and the previous matrix data.
   * @param comm The previous communication matrix.
   * @param groups The array of groups created based on the previous matrix.
   * @param ngroups The amount of groups in the groups array.
   */
  static void recreate_matrix(CommMatrix &comm, Group *groups, const UInt &ngroups);

  /**
   * @brief Returns the indice of the element (row) in the matrix with the greatest communication value sum.
   * @details This is used to select the first element in a group when invoking generate_groups
   * @param comm The communication matrix.
   */
  static IndexType most_communicating_row(const CommMatrix &comm);
};

#include "eagerMapAlgorithm.ipp"

}