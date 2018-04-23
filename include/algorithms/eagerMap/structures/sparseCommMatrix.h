#pragma once

#include <vector>
#include <map>

namespace EagerMap {

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

  MatrixCell& operator[](const IndexType &i) {
    return elements[i];
  }

  MatrixCell& at(const IndexType &i) {
    return operator[](i);
  }

  CommunicationSparseMatrix(typename DataArray::size_type size) : elements(DataArray(size)) {
    for(decltype(size) i = 0; i < size; ++i)
      elements[i] = MatrixCell();
  }

};

}