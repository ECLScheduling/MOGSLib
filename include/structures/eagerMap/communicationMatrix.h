#pragma once

#include <system/traits.h>
#include <structures/matrix1d.h>

namespace EagerMap {

/**
 * This class is a specialization the Matrix1d used to represent the Communication of threads. Some methods to auxiliate the EagerMap algorithm are implemented here.
 */
class CommunicationMatrix : public Matrix1D<typename EagerMapTraits::UInt, typename EagerMapTraits::CommValue> {
private:
  typedef Matrix1D<IndexType, ValueType> BaseMatrixClass; 
  
public:

  /**
   * A constructor that initializes all the needed internal state.
   * @param matrixOrder The matrix magnitude.
   */
  CommunicationMatrix(const IndexType &matrixOrder) : BaseMatrixClass(matrixOrder) {}

  /**
   * A constructor that initializes the internal state and initializes the matrix with a default value.
   * @param order The order of the communication matrix.
   * @param defaultVal The default value for all the cells in the matrix.
   */
  CommunicationMatrix(const IndexType &matrixOrder, const ValueType &defaultVal) : BaseMatrixClass(matrixOrder, defaultVal) {}

  virtual ~CommunicationMatrix() {}

  /**
   * Gets the sum of the communication values of a row.
   * @param aRow The row that will have all it's values added together.
   */
  const ValueType rowSum(const IndexType &aRow) const {
    ValueType * rowPtr = row(aRow);

    ValueType sum = 0;

    // This method is implemented using two fors to avoid having a if-check to ignore the main diagonal.
    for(IndexType i = 0; i < aRow; ++i)
      sum += rowPtr[i];
    for(IndexType i = aRow+1; i < order; ++i)
      sum += rowPtr[i];

    return sum;
  }

  /**
   * Gets the row index where the index's value sum is the greatest, excluding the indices that are filtered.
   * @details Any indice marked as true in the boolean parameter is excluded from the analysis. A filter that prevents all values to be tested is not considered sane and will fail an assertion.
   * @param filter The indices that are marked to be ignored by the algorithm.
   */
  const IndexType filteredMaxRowSum(const bool * const filter) const {
    ValueType max = 0;
    IndexType curMax = 0;

    bool saneFiler = false;

    for(IndexType i = 0; i < order; ++i) {
      if(filter[i] == true)
        continue;

      ValueType sum = rowSum(i);
      saneFiler = true;

      if(sum > max) {
        max = sum;
        curMax = i;
      }
    }

    assert(saneFiler);
    return curMax;
  }

};

}