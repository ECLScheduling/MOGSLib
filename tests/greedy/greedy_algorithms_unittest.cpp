#include <gtest/gtest.h>

#include <algorithms/greedy/greedyAlgorithm.h>
#include <system/debug.h>

namespace Greedy_Tests {

/**
 * @brief This class is a helper class to test the Greedy Strategy Algorithms.
 */
class AlgorithmsTest : public ::testing::Test {
public:
  using UInt = typename Traits<DefaultTypes>::UInt;
  using Load = UInt;

  using Algorithm = Greedy::Algorithms<Load, UInt>;

  UInt *map;
  Load *loads;
  UInt n;

  void SetUp() {
    map = nullptr;
    loads = nullptr;
  }

  void TearDown() {
    if(map != nullptr){
      delete [] map;
      map = nullptr;
    }
    if(loads != nullptr){
      delete [] loads;
      loads = nullptr;
    }
  }

  void initMap(const UInt size) {
    map = new UInt[size]();
    for(UInt i = 0; i < size; ++i) {
      map[i] = i;
    }
  }

  void test_case1() {
    n = 10;
    loads = new Load[n]();
    loads[0] = 1;
    loads[1] = 3;
    loads[2] = 4;
    loads[3] = 8;
    loads[4] = 5;
    loads[5] = 6;
    loads[6] = 2;
    loads[7] = 9;
    loads[8] = 7;
    loads[9] = 10;
    initMap(n);
  }

  void test_case2() {
    n = 10;
    loads = new Load[n]();
    loads[0] = 1;
    loads[1] = 2;
    loads[2] = 3;
    loads[3] = 4;
    loads[4] = 5;
    loads[5] = 6;
    loads[6] = 7;
    loads[7] = 8;
    loads[8] = 9;
    loads[9] = 10;
    initMap(n);
  }

  void test_case3() {
    n = 8;
    loads = new Load[n]();
    loads[0] = 2;
    loads[1] = 6;
    loads[2] = 8;
    loads[3] = 4;
    loads[4] = 14;
    loads[5] = 12;
    loads[6] = 16;
    loads[7] = 10;
    initMap(n);
  }

};

TEST_F(AlgorithmsTest, tasksMustHaveDecrescentOrdering) {
  test_case1();
  UInt expected_map[] = {9, 7, 3, 8, 5, 4, 2, 1, 6, 0};

  Algorithm::order_tasks(loads, n, map);

  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(map[i], expected_map[i]);
  }
}

TEST_F(AlgorithmsTest, tasksMustHaveDecrescentOrdering2) {
  test_case2();
  UInt expected_map[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  Algorithm::order_tasks(loads, n, map);

  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  for(UInt i = 0; i < n; ++i) {
    EXPECT_EQ(map[i], expected_map[i]);
  }
}

TEST_F(AlgorithmsTest, PEsMustBeOrderedInABinaryHeap) {
  test_case1();
  UInt expected_map[] = {0, 1, 6, 8, 4, 5, 2, 7, 3, 9};

  Algorithm::order_PEs(loads, n, map);

  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  for(UInt i = 0; i < n; ++i)
    EXPECT_EQ(map[i], expected_map[i]);
}

TEST_F(AlgorithmsTest, PEsMustBeOrderedInABinaryHeap2) {
  test_case2();
  UInt expected_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  Algorithm::order_PEs(loads, n, map);

  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  for(UInt i = 0; i < n; ++i)
    EXPECT_EQ(map[i], expected_map[i]);
}

TEST_F(AlgorithmsTest, PEsMustBeKeptInOrderAfterUpdated) {
  test_case3();

  Algorithm::order_PEs(loads, n, map);

  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  loads[map[0]] = 3; // from 2 to 3; should not alter anything.

  UInt expected_map[] = {0, 3, 2, 1, 4, 5, 6, 7};
  Algorithm::reorder_PEs(loads, map, n);

  debug_trc<LibTests>() << "\nAfter updating head...\n";
  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  for(UInt i = 0; i < n; ++i)
    EXPECT_EQ(map[i], expected_map[i]);
}

TEST_F(AlgorithmsTest, PEsMustBeKeptInOrderAfterUpdated_2) {
  test_case3();

  Algorithm::order_PEs(loads, n, map);

  debug_trc<LibTests>() << "Before updating any PE's load: " << "\n";
  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  loads[map[0]] = 5; // from 2 to 3; should sift down once.
  UInt expected_map[] = {3, 0, 2, 1, 4, 5, 6, 7};
  Algorithm::reorder_PEs(loads, map, n);

  debug_trc<LibTests>() << "\nAfter updating head...\n";
  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  for(UInt i = 0; i < n; ++i)
    EXPECT_EQ(map[i], expected_map[i]);
}

TEST_F(AlgorithmsTest, PEsMustBeKeptInOrderAfterUpdated_3) {
  test_case3();

  Algorithm::order_PEs(loads, n, map);

  debug_trc<LibTests>() << "Before updating any PE's load: " << "\n";
  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  loads[map[0]] = 18; // from 2 to 3; should sift down to the bottom.
  UInt expected_map[] = {3, 1, 2, 7, 4, 5, 6, 0};
  Algorithm::reorder_PEs(loads, map, n);

  debug_trc<LibTests>() << "\nAfter updating head...\n";
  for(UInt i = 0; i < n; ++i)
    debug_trc<LibTests>() << "map: " << map[i] << ". val: " << loads[i] << "\n";

  for(UInt i = 0; i < n; ++i)
    EXPECT_EQ(map[i], expected_map[i]);
}

}