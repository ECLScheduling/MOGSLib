#include <gtest/gtest.h>

#include <algorithms/binLPT/binLPTAlgorithm.h>
#include <system/traits.h>

namespace BinLPT_ComputeChunkLoadTest_Test {

/**
 * @brief This class is a helper class to test the BinLPT Partition Chunk function.
 */
class ComputeChunkLoadTest : public ::testing::Test {
private:
  bool loads_allocated;

public:

  using UInt = Traits<DefaultTypes>::UInt;
  using Load = Traits<DefaultTypes>::Load;

  using Algorithms = BinLPT::Algorithms<Load, UInt>;

  /**
   * @variable loads Array of load information to be referenced inside load_info.
   */
  std::vector<Load> loads;

  /**
   * @variable nchunks The amount of chunks to be made.
   */
  UInt nchunks, ntasks;

  /**
   * @variable output The tested function's output
   * @variable chunk_sizes The size of the chunks.
   */
  UInt *output, *chunk_sizes;

  void initializeLoads() {
    for(UInt i = 0; i < ntasks; ++i) {
      loads.push_back(i+1);
    }
  }

  void initializeLoadsLargerFirst() {
    for(UInt i = 0; i < ntasks; ++i) {
      loads.push_back(ntasks-i);
    }
  }

  void TearDown() {
    loads.clear();
  }

  void testFunction() {
    chunk_sizes = Algorithms::compute_chunksizes(loads.data(), loads.size(), nchunks);
    output = Algorithms::compute_chunkloads(loads.data(), loads.size(), chunk_sizes, nchunks);
  }

};

TEST_F(ComputeChunkLoadTest, emptyChunk) {
  nchunks = 1;
  ntasks = 0;

  //initializeLoads();

  testFunction();

  EXPECT_EQ(output[0], 0);
}

TEST_F(ComputeChunkLoadTest, oneTask) {
  nchunks = 1;
  ntasks = 1;

  initializeLoads(); // 1

  testFunction();

  EXPECT_EQ(output[0], 1);
}

TEST_F(ComputeChunkLoadTest, oneTaskTwoChunks) {
  nchunks = 2;
  ntasks = 1;

  initializeLoads(); // 1

  testFunction();

  EXPECT_EQ(output[0], 1);
  EXPECT_EQ(output[1], 0);
}

TEST_F(ComputeChunkLoadTest, twoTaskOneChunk) {
  nchunks = 1;
  ntasks = 2;

  initializeLoads(); // 1, 2

  testFunction();

  EXPECT_EQ(output[0], 3);
}

TEST_F(ComputeChunkLoadTest, taskSet) {
  nchunks = 2;
  ntasks = 5;

  initializeLoads(); // 1, 2, 3, 4, 5 ; Average/Chunk = 7

  testFunction(); // Chunk[0] = 1,2,3,4 (10) ; Chunk[1] = 5 (5)

  EXPECT_EQ(output[0], 10);
  EXPECT_EQ(output[1], 5);
}

TEST_F(ComputeChunkLoadTest, inverseTaskSet) {
  nchunks = 2;
  ntasks = 5;

  initializeLoadsLargerFirst(); // 5,4,3,2,1 ; Average/Chunk = 7

  testFunction(); // Chunk[0] = 5,4 (9) ; Chunk[1] = 3,2,1 (6)

  EXPECT_EQ(output[0], 9);
  EXPECT_EQ(output[1], 6);
}

TEST_F(ComputeChunkLoadTest, moreChunks) {
  nchunks = 5;
  ntasks = 10;

  initializeLoadsLargerFirst(); // 10,9,8,7,6,5,4,3,2,1 ; Average/Chunk = 11

  testFunction(); // Chunk[0] = 10,9 (19) ; Chunk[1] = 7,8 (15) ; Chunk[2] = 6,5,4 (15) ; Chunk[3] = 3,2,1 (6) ; Chunk[4] = (0);

  EXPECT_EQ(output[0], 19);
  EXPECT_EQ(output[1], 15);
  EXPECT_EQ(output[2], 15);
  EXPECT_EQ(output[3], 6);
  EXPECT_EQ(output[4], 0);
}

}