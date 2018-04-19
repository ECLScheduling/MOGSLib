#pragma once

#include <system/traits.h>
#include <algorithms/utility.h>
#include "structures/sparseMatrix.h"

namespace EagerMap {

using UInt = Traits<DefaultTypes>::UInt;

/**
 * @brief The struct that defines a sparse matrix tuned for the EagerMap algorithm.
 *
 * @type IndexType The type that represents a task id for which the communication is targeted.
 * @type DataType The type that represents the communication quantity.
 */
template<typename IndexType, typename DataType>
struct CommunicationSparseMatrix {
  using MatrixCell = std::map<IndexType, DataType>;
  using DataArray = std::vector<MatrixCell>;
  
  DataArray elements;

  CommunicationSparseMatrix(DataArray::size_type size) : elements(DataArray(size)) {
    for(decltype(size) i = 0; i < size; ++i)
      elements[] = MatrixCell();
  };
};

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
  using Group = std::vector<IndexType>;

  /**
   * @brief Generates a group of tasks based on communication affinity.
   * @param comm The communication matrix.
   * @param total_elements The total amount of elements (rows) in the matrix.
   * @param group_elements The wanted size of the generated group.
   * @param chosen a boolean array to mark the chosen elements for a group to avoid selecting the same element twice.
   * @param previous_groups The array containing the groups of previous iterations.
   */
  static Group* generate_groups(CommMatrix comm, UInt total_elements, UInt group_elements, bool *chosen, Groups *previous_groups);

private:

  /**
   * @brief Returns the indice of the element (row) in the matrix with the greatest communication value sum.
   * @details This is used to select the first element in a group when invoking generate_groups
   * @param comm The communication matrix.
   */
  static IndexType most_communicating_row(const CommMatrix &comm);

  /**
   * @brief Register an element to a group.
   * @details This method has been separated from generate_groups because it was used in different parts of the algorithm.
   */
  static inline void register_in_group(const UInt &winner, Group *group, const UInt &pos, bool *chosen, Groups *previous_groups) {
    chosen[winner] = true;
    group[pos] = previous_groups[winner];
  }
};

#include "eagerMapAlgorithm.ipp"

}