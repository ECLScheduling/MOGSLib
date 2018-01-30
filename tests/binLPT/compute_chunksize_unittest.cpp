#include <gtest/gtest.h>

#include <algorithms/binLPT/binLPTAlgorithm.h>
#include <system/traits.h>

namespace BinLPT_ComputeChunkSizeTest_Test {

/**
 * @brief This class is a helper class to test the BinLPT Partition Chunk function.
 */
class ComputeChunkSizeTest : public ::testing::Test {
private:
  bool loads_allocated;

public:

  using UInt = Traits<void>::UInt;
  using Load = Traits<void>::Load;

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
   */
  UInt *output;

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

  void callTestFunction() {
    output = Algorithms::compute_chunksizes(loads.data(), loads.size(), nchunks); 
  }

};

TEST_F(ComputeChunkSizeTest, emptyLoadInfoShouldUseOneChunkWithNoTasks) {
  nchunks = 1;
  ntasks = 0;

  callTestFunction();

  EXPECT_EQ(output[0], 0);
}

TEST_F(ComputeChunkSizeTest, emptyLoadInfoShouldTwoChunksWithNoTasks) {
  nchunks = 2;
  ntasks = 0;

  callTestFunction();

  EXPECT_EQ(output[0], 0);
  EXPECT_EQ(output[1], 0);
}

TEST_F(ComputeChunkSizeTest, partitionOneTask) {
  nchunks = 2;
  ntasks = 1;

  initializeLoads();
  callTestFunction();

  EXPECT_EQ(output[0], 1);
  EXPECT_EQ(output[1], 0);
}

TEST_F(ComputeChunkSizeTest, partitionTwoEqualTasks) {
  nchunks = 2;
  ntasks = 2;

  initializeLoads();
  loads[0] = 1;
  loads[1] = 1;

  callTestFunction();

  EXPECT_EQ(output[0], 2);
  EXPECT_EQ(output[1], 0);
}

TEST_F(ComputeChunkSizeTest, partitionTwoDifferentTasks) {
  nchunks = 2;
  ntasks = 2;

  initializeLoads();
  loads[0] = 2;
  loads[1] = 1;

  callTestFunction();

  EXPECT_EQ(output[1], 1);
  EXPECT_EQ(output[1], 1);
}

TEST_F(ComputeChunkSizeTest, partitionTaskSet) {
  nchunks = 2;
  ntasks = 5;

  initializeLoads(); // 1,2,3,4,5; Average Load/Chunk = 7

  callTestFunction();

  EXPECT_EQ(output[0], 4); // 1, 2, 3, 4
  EXPECT_EQ(output[1], 1); // 5
}

TEST_F(ComputeChunkSizeTest, partitionInverseTaskSet) {
  nchunks = 2;
  ntasks = 5;

  initializeLoadsLargerFirst(); // 5,4,3,2,1; Average Load/Chunk = 7

  callTestFunction();

  EXPECT_EQ(output[0], 2); // 5,4
  EXPECT_EQ(output[1], 3); // 3,2,1
}

TEST_F(ComputeChunkSizeTest, partitionInverseTaskSetMoreChunks) {
  nchunks = 3;
  ntasks = 5;

  initializeLoadsLargerFirst(); // 5,4,3,2,1; Average Load/Chunk = 5

  callTestFunction();

  EXPECT_EQ(output[0], 2); // 5,4
  EXPECT_EQ(output[1], 3); // 3,2,1
  EXPECT_EQ(output[2], 0); // 3,2,1
}

}