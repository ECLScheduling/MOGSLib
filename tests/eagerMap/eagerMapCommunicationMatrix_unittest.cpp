#include <gtest/gtest.h>
#include <system/traits.h>

#include <structures/eagerMap/communicationMatrix.h>

#include <iostream>
#include <queue>

namespace EagerMapCommunicationTests {

/**
 * Fixture for testing the EagerMapCommunicationMatrix structure.
 */
class MatrixTests : public ::testing::Test {
public:
  typedef EagerMapTraits::CommunicationMatrix CommunicationMatrix;
  typedef CommunicationMatrix::IndexType Index;
  typedef CommunicationMatrix::ValueType CommValue;

  CommunicationMatrix *matrix;

  void SetUp() {
    createdMatrix = false;
  }

  void createMatrix(const Index &order) {
    matrix = new CommunicationMatrix(order);
  }

  void initializeMatrix(const Index &order, const CommValue *values) {
    auto totalElements = order*order;
    for(Index i = 0; i < totalElements; ++i)
        matrix->at(0,i) = values[i];
  }

  void TearDown() {
    
    if(createdMatrix){
      createdMatrix = false;
      delete matrix;
    }
  }

private:

  bool createdMatrix;
};

/**
 * This class contains a simple data-set to test the navigation functions.
 */
class MatrixNavigationTests : public MatrixTests {
public:

  Index anOrder;
  CommValue *values;

  void SetUp() {
    MatrixTests::SetUp();

    anOrder = 3;
    values = new CommValue[anOrder*anOrder];
    for(Index i = 0; i < anOrder*anOrder; ++i)
      values[i] = i+1;  
    

    createMatrix(anOrder);
    initializeMatrix(anOrder, values);
  }

  void TearDown() {
    MatrixTests::TearDown();
    delete values;
  }

};

/**
 * Test if all the elements are populated and accessed in a correct way.
 */
TEST_F(MatrixNavigationTests, accessValue) {
  for(Index i = 0; i < anOrder; ++i) {
    for(Index j = 0; j < anOrder; ++j) {
      EXPECT_EQ(values[i*anOrder + j], matrix->at(i,j));
    }
  }
}

/**
 * Test if all the rows are populated and accessed in a correct way.
 */
TEST_F(MatrixNavigationTests, accessRow) {
  for(Index i = 0; i < anOrder; ++i) {
    CommValue *row = matrix->row(i);
    for(Index j = 0; j < anOrder; ++j) {
      EXPECT_EQ(values[i*anOrder + j], row[j]);
    }
  }
}

TEST_F(MatrixTests, rowSum) {
  const Index anOrder = 3;

  const CommValue values[anOrder * anOrder] = {0,1,1,3,0,3,2,2,0};
  const CommValue expectedRowSums[] = {2, 6, 4};

  createMatrix(anOrder);
  initializeMatrix(anOrder, values);

  for(Index i = 0; i < anOrder; ++i) {
    ASSERT_EQ(expectedRowSums[i], matrix->rowSum(i));
  }
}

TEST_F(MatrixTests, maxRowSum) {
  const Index anOrder = 3;

  const CommValue values[anOrder * anOrder] = {0,1,1,3,0,3,2,2,0};
  const Index expectedRowMax = 1;

  bool filter[anOrder];
  for(Index i = 0; i < anOrder; ++i)
    filter[i] = false;  

  createMatrix(anOrder);
  initializeMatrix(anOrder, values);

  ASSERT_EQ(expectedRowMax, matrix->filteredMaxRowSum(filter));
}

TEST_F(MatrixTests, rowSum4Elements) {
  const Index anOrder = 4;

  const CommValue values[anOrder * anOrder] = {0,1,1,1, 3,0,3,3, 2,2,0,2, 4,4,4,0};
  const CommValue expectedRowSums[] = {3, 9, 6, 12};

  createMatrix(anOrder);
  initializeMatrix(anOrder, values);

  for(Index i = 0; i < anOrder; ++i) {
    ASSERT_EQ(expectedRowSums[i], matrix->rowSum(i));
  }
}

TEST_F(MatrixTests, maxRowSum4Elements) {
  const Index anOrder = 4;

  const CommValue values[anOrder * anOrder] = {0,1,1,1, 3,0,3,3, 2,2,0,2, 4,4,4,0};
  const Index expectedRowMax = 3;

  bool filter[anOrder];
  for(Index i = 0; i < anOrder; ++i)
    filter[i] = false;

  createMatrix(anOrder);
  initializeMatrix(anOrder, values);

  ASSERT_EQ(expectedRowMax, matrix->filteredMaxRowSum(filter));
}

TEST_F(MatrixTests, maxRowFilterTest) {
  const Index anOrder = 4;

  const CommValue values[anOrder * anOrder] = {0,1,1,1, 3,0,3,3, 2,2,0,2, 4,4,4,0};
  const Index expectedRowMax = 1;

  bool filter[anOrder];
  for(Index i = 0; i < anOrder; ++i)
    filter[i] = false;
  filter[3] = true;

  createMatrix(anOrder);
  initializeMatrix(anOrder, values);

  ASSERT_EQ(expectedRowMax, matrix->filteredMaxRowSum(filter));
}

TEST_F(MatrixTests, maxRowAllButOneFilterTest) {
  const Index anOrder = 4;

  const CommValue values[anOrder * anOrder] = {0,1,1,1, 3,0,3,3, 2,2,0,2, 4,4,4,0};
  const Index expectedRowMax = 0;

  bool filter[anOrder];
  for(Index i = 0; i < anOrder; ++i)
    filter[i] = true;
  filter[0] = false;

  createMatrix(anOrder);
  initializeMatrix(anOrder, values);

  ASSERT_EQ(expectedRowMax, matrix->filteredMaxRowSum(filter));
}

TEST_F(MatrixTests, maxRowSaneFilterTest) {
  const Index anOrder = 4;

  const CommValue values[anOrder * anOrder] = {0,1,1,1, 3,0,3,3, 2,2,0,2, 4,4,4,0};

  bool filter[anOrder];
  for(Index i = 0; i < anOrder; ++i)
    filter[i] = true;

  createMatrix(anOrder);
  initializeMatrix(anOrder, values);

  ASSERT_DEATH(matrix->filteredMaxRowSum(filter), "");
}

}