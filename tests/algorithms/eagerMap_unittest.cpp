#include <gtest/gtest.h>

#include <algorithms/eagerMap/structures/sparseMatrix.h>

#include <system/debug.h>

namespace EagerMap_Algorithms_Test {

using UInt = Traits<DefaultTypes>::UInt;

/**
 * @brief This class is a helper class to test the algorithms in the utility namespace.
 */
class AlgorithmsTest : public ::testing::Test {
public:

  void SetUp() {
  }

  void TearDown() {
  }

};

TEST_F(AlgorithmsTest, sparse_matrix_row) {
  Structures::SparseMatrixRow<int> int_row;
  int element = 1;
  int element2 = 2;

  int_row.push(element);
  int_row.push(element2);

  ASSERT_EQ(int_row.size(), 2);
  ASSERT_EQ(int_row[0], element);
  ASSERT_EQ(int_row[1], element2);

  int_row.remove(1);

  ASSERT_EQ(int_row.size(), 1);
  ASSERT_EQ(int_row[0], element);
}

TEST_F(AlgorithmsTest, sparse_matrix_static_row) {
  Structures::SparseMatrixRowStatic<int, 2> int_row;
  int element = 1;
  int element2 = 2;

  ASSERT_EQ(int_row.size(), 2);

  int_row[0] = element;
  int_row[1] = element2;

  ASSERT_EQ(int_row[0], element);
  ASSERT_EQ(int_row[1], element2);
}

TEST_F(AlgorithmsTest, sparse_matrix_fixed_size) {
  const auto matrix_row_count = 2;
  const auto matrix_colum_count = 3;
  
  Structures::SparseMatrix<int, matrix_row_count> matrix;
  int *elements = new int[matrix_colum_count*matrix_row_count];

  for(auto i = 0; i < matrix_colum_count*matrix_row_count; ++i)
    elements[i] = i;

  for(auto i = 0; i < matrix_row_count*matrix_colum_count; ++i)
    matrix[i%matrix_row_count].push(elements[i]);

  ASSERT_EQ(matrix.size(), matrix_row_count);
  for(auto i = 0; i < matrix_row_count; ++i)
    ASSERT_EQ(matrix[i].size(), matrix_colum_count);

  delete [] elements;
}

TEST_F(AlgorithmsTest, sparse_matrix_dynamic_size) {
  const auto matrix_row_count = 2;
  const auto matrix_colum_count = 3;
  
  Structures::DynamicSparseMatrix<int> matrix;
  auto *rows = new decltype(matrix)::value_type[matrix_row_count];
  int *elements = new int[matrix_colum_count*matrix_row_count];

  // Creates all the elements
  for(auto i = 0; i < matrix_colum_count*matrix_row_count; ++i)
    elements[i] = i;

  // Add the elements to the respective rows
  for(auto i = 0; i < matrix_row_count*matrix_colum_count; ++i)
    rows[i%matrix_row_count].push(elements[i]);

  // Add the rows into the matrix
  for(auto i = 0; i < matrix_row_count; ++i)
    matrix.push(rows[i]);

  ASSERT_EQ(matrix.size(), matrix_row_count);
  for(auto i = 0; i < matrix_row_count; ++i)
    ASSERT_EQ(matrix[i].size(), matrix_colum_count);

  delete [] elements;
  delete [] rows;
}

}