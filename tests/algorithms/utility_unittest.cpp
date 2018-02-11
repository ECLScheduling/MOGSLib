#include <gtest/gtest.h>

#include <algorithms/utility.h>

#include <system/debug.h>

namespace Utility_Algorithms_Test {

using UInt = Traits<DefaultTypes>::UInt;
using T = UInt;

/**
 * @brief This class is a helper class to test the algorithms in the utility namespace.
 */
class AlgorithmsTest : public ::testing::Test {
public:

  T *A;
  UInt n;
  UInt *map;

  void SetUp() {
    A = nullptr;
    map = nullptr;
  }

  void TearDown() {
    if(A != nullptr){
      delete [] A;
      A = nullptr;
    }
    if(map != nullptr){
      delete [] map;
      map = nullptr;
    }
  }

  void createMap(UInt size) {
    map = new UInt[size]();
    for(UInt i = 0; i < size; ++i) {
      map[i] = i;
    }
  }

  void createTest1() {
    n = 8;
    createMap(n);

    A = new T[n]();
    A[0] = 1;
    A[1] = 4;
    A[2] = 2;
    A[3] = 6;
    A[4] = 7;
    A[5] = 5;
    A[6] = 8;
    A[7] = 3;
  }

  void createTest2() {
    n = 8;
    createMap(n);

    A = new T[n]();
    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
    A[3] = 4;
    A[4] = 5;
    A[5] = 6;
    A[6] = 7;
    A[7] = 8;
  }

  void createTest3() {
    n = 8;
    createMap(n);

    A = new T[n]();
    A[0] = 8;
    A[1] = 7;
    A[2] = 6;
    A[3] = 5;
    A[4] = 4;
    A[5] = 3;
    A[6] = 2;
    A[7] = 1;
  }
};

/**
 * #################### Heap Sort Tests ##########################
 */

TEST_F(AlgorithmsTest, make_heap1) {
  createTest1();

  UInt expected_map[] = {6, 4, 5, 3, 1, 0, 2, 7};
  T expected_output[] = {8, 7, 5, 6, 4, 1, 2, 3};

  UtilityAlgorithms::make_heap<T, UInt, false>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, make_heap2) {
  createTest2();
  UInt expected_map[] = {7, 4, 6, 3, 0, 5, 2, 1};
  T expected_output[] = {8, 5, 7, 4, 1, 6, 3, 2};

  UtilityAlgorithms::make_heap<T, UInt, false>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, make_heap3) {
  createTest3();
  UInt expected_map[] = {0, 1, 2, 3, 4, 5, 6, 7};
  T expected_output[] = {8, 7, 6, 5, 4, 3, 2, 1};

  UtilityAlgorithms::make_heap<T, UInt, false>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, make_heap_ascending_order1) {
  createTest1();
  UInt expected_map[] = {0, 7, 2, 1, 4, 5, 6, 3};
  T expected_output[] = {1, 3, 2, 4, 7, 5, 8, 6};

  UtilityAlgorithms::make_heap<T, UInt, true>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, make_heap_ascending_order2) {
  createTest2();
  UInt expected_map[] = {0, 1, 2, 3, 4, 5, 6, 7};
  T expected_output[] = {1, 2, 3, 4, 5, 6, 7, 8};

  UtilityAlgorithms::make_heap<T, UInt, true>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, make_heap_ascending_order3) {
  createTest3();
  UInt expected_map[] = {7, 4, 6, 3, 0, 5, 2, 1};
  T expected_output[] = {1, 4, 2, 5, 8, 3, 6, 7};

  UtilityAlgorithms::make_heap<T, UInt, true>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

/**
 * #################### Insertion Sort Tests ##########################
 */

TEST_F(AlgorithmsTest, insertion_sort1) {
  createTest1();
  UInt expected_map[] = {6, 4, 3, 5, 1, 7, 2, 0};
  T expected_output[] = {8, 7, 6, 5, 4, 3, 2, 1};

  UtilityAlgorithms::insertion_sort<T, UInt, false>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, insertion_sort2) {
  createTest2();
  UInt expected_map[] = {7, 6, 5, 4, 3, 2, 1, 0};
  T expected_output[] = {8, 7, 6, 5, 4, 3, 2, 1};

  UtilityAlgorithms::insertion_sort<T, UInt, false>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, insertion_sort3) {
  createTest3();
  UInt expected_map[] = {0, 1, 2, 3, 4, 5, 6, 7};
  T expected_output[] = {8, 7, 6, 5, 4, 3, 2, 1};

  UtilityAlgorithms::insertion_sort<T, UInt, false>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, insertion_sort_ascending1) {
  createTest1();
  UInt expected_map[] = {0, 2, 7, 1, 5, 3, 4, 6};
  T expected_output[] = {1, 2, 3, 4, 5, 6, 7, 8};

  UtilityAlgorithms::insertion_sort<T, UInt, true>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, insertion_sort_ascending2) {
  createTest2();
  UInt expected_map[] = {0, 1, 2, 3, 4, 5, 6, 7};
  T expected_output[] = {1, 2, 3, 4, 5, 6, 7, 8};

  UtilityAlgorithms::insertion_sort<T, UInt, true>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

TEST_F(AlgorithmsTest, insertion_sort_ascending3) {
  createTest3();
  UInt expected_map[] = {7, 6, 5, 4, 3, 2, 1, 0};
  T expected_output[] = {1, 2, 3, 4, 5, 6, 7, 8};

  UtilityAlgorithms::insertion_sort<T, UInt, true>(map, A, n);

  for(UInt i = 0; i < n; ++i) {
    debug<LibTests>(trace) << "map: " << map[i] << ". val: " << A[i] << "\n";
  }

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(expected_output[i], A[i]);
    EXPECT_EQ(expected_map[i], map[i]);
  }
}

}