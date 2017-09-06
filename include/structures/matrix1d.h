#pragma once

#include <cassert>
#include <cstring>

/**
 * A generic typed value and generic typed indexed square matrix that has it's elements stored in a unidimensional array.
 * @type IndexType The type that dictates the index of the matrix.
 * @type ValueType The type of information the matrix stores.
 */
template<typename anIndexType, typename aValueType>
class Matrix1D {
public:
  typedef anIndexType IndexType;
  typedef aValueType ValueType;

  /**
   * The matrix data structure, stored in the form of an array.
   */
  ValueType *matrix;

  /**
   * The order of the communication matrix.
   */
  IndexType order;

  /**
   * A constructor that initializes the internal state.
   * @param order The order of the communication matrix.
   */
  Matrix1D(const IndexType &matrixOrder) : order(matrixOrder) {
    matrix = new ValueType[order*order];
  }

  /**
   * A constructor that initializes the internal state and initializes the matrix with a default value.
   * @param order The order of the communication matrix.
   * @param defaultVal The default value for all the cells in the matrix.
   */
  Matrix1D(const IndexType &matrixOrder, const ValueType &defaultVal) : order(matrixOrder) {
    matrix = new ValueType[order*order];
   
    std::memset(matrix, defaultVal, sizeof(ValueType) * (order*order));
  }

  /**
   * A destructor that frees the used memory.
   */
  virtual ~Matrix1D() {
    delete [] matrix;
  }

  /**
   * Gets a reference to the communication value from the matrix.
   * @param row The row of the matrix.
   * @param col The col of the matrix.
   */
  inline ValueType& at(const IndexType &row, const IndexType &col) const {
    return at(row,col,order);
  }

  /**
   * Gets a reference to the communication value from the matrix.
   * @param row The row of the matrix.
   * @param col The col of the matrix.
   * @param usedOrdering The assumed ordering of the matrix.
   */
  inline ValueType& at(const IndexType &row, const IndexType &col, const IndexType &usedOrdering) const {
    assert(row < usedOrdering); // There are no row assertions in order to be able to traverse the whole matrix as an 1d array.
    
    return matrix[row * usedOrdering + col];
  }

  /**
   * Gets a constant reference to the communication value's row.
   * @param row The row of the matrix.
   */
  inline ValueType * const row(const IndexType &row) const {
    assert(row < order);
    
    return &(matrix[row * order]);
  }

};