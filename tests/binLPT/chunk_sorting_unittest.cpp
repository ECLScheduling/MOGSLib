#include <gtest/gtest.h>
#include <structures/binLPT/chunkSorting.h>
#include <system/traits.h>

namespace BinLPT_Chunk_Sorting_Test {

/**
 * This class is a helper class to test the BinLPT Chunk sorting meta-structure.
 */
class ChunkSortingTest : public ::testing::Test {
public:

  using UInt = Traits<void>::UInt;
  using Load = UInt;
  using LoadSetInfo = BinLPT::LoadSetInfo<Load, UInt>;
  using Chunks = BinLPT::TaskChunks<Load, UInt>;

  using CountingSort = BinLPT::ChunkSorting<Load, UInt, false>;
  using QuickSort = BinLPT::ChunkSorting<Load, UInt, true>;

  LoadSetInfo *load_info;
  static const UInt chunk_count = 5;

  const UInt input[chunk_count] = {3, 4, 1, 2, 0};
  const UInt expected_output[chunk_count] = {1, 0, 3, 2, 4};
  
  std::vector<UInt> indexes_vector;


  void SetUp() {
    load_info = new LoadSetInfo();
    load_info->chunks = new Chunks(chunk_count);

    for(UInt i = 0; i < chunk_count; ++i) {
      load_info->chunks->load_sum[i] = input[i];  
      indexes_vector.push_back(i);
    }
  }

  void TearDown() {
    indexes_vector.clear();
    delete load_info;
  }

};

TEST_F(ChunkSortingTest, testCountingSort) {
  CountingSort::function(*load_info, indexes_vector);

  for(UInt i = 0; i < chunk_count; ++i)
    EXPECT_EQ(indexes_vector[i], expected_output[i]);
}

TEST_F(ChunkSortingTest, testQuickSort) {
  QuickSort::function(*load_info, indexes_vector);

  for(UInt i = 0; i < chunk_count; ++i)
    EXPECT_EQ(indexes_vector[i], expected_output[i]);
}

}