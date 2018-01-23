#include <gtest/gtest.h>
#include <system/traits.h>
#include <algorithms/binLPT/binLPTAlgorithm.h>

#include <iostream>

namespace BinLPT_PartitionChunks_Test {

/**
 * This class is a helper class to test the BinLPT Partition Chunk function.
 */
class PartitionChunksTest : public ::testing::Test {
private:
  bool loads_allocated;

public:

  using UInt = Traits<void>::UInt;
  using Load = Traits<void>::Load;

  using Algorithms = BinLPT::Algorithms<Load, UInt>;
  using LoadSetInfo = BinLPT::LoadSetInfo<Load, UInt>;
  using TaskChunks = BinLPT::TaskChunks<Load, UInt>;

  /**
   * load info input that is used in the partitionChunks function.
   */
  LoadSetInfo *load_info;

  /**
   * Array sizes for loads and chunks.
   */
  UInt load_size, chunk_size;

  /**
   * Array of load information to be referenced inside load_info.
   */
  std::vector<Load> loads;

  void initializeLoads() {
    for(UInt i = 0; i < load_size; ++i) {
      loads.push_back(i+1);
    }
  }

  void initializeLoadsLargerFirst() {
    for(UInt i = 0; i < load_size; ++i) {
      loads.push_back(load_size-i);
    }
  }

  void initializeLoadSetInfo() {
    load_info = LoadSetInfo::analyzeLoadArray(loads, chunk_size);
  }

  void SetUp() {
    loads_allocated = 0;
  }

  void TearDown() {
    loads.clear();
    delete load_info;
  }

  void callTestFunction() {
    Algorithms::partitionChunks(*load_info); 
  }

};

TEST_F(PartitionChunksTest, emptyLoadInfoShouldUseOneChunkWithNoTasks) {
  chunk_size = 1;
  load_size = 0;
  initializeLoadSetInfo();

  callTestFunction();

  EXPECT_EQ(load_info->chunks->load_sum[0], 0);
  EXPECT_EQ(load_info->chunks->tasks[0].size(), 0);
}

TEST_F(PartitionChunksTest, partitionSingleTaskTest) {
  chunk_size = 2;
  load_size = 1;

  initializeLoads();
  initializeLoadSetInfo();

  callTestFunction();

  EXPECT_EQ(load_info->chunks->load_sum[0], loads[0]);
  EXPECT_EQ(load_info->chunks->tasks[0].size(), 1);
}

TEST_F(PartitionChunksTest, partitionTwoEqualTasksTest) {
  chunk_size = 2;
  load_size = 2;

  initializeLoads();
  loads[0] = 1;
  loads[1] = 1;
  initializeLoadSetInfo(); // Should chunk as (1) and (1)

  callTestFunction();

  EXPECT_EQ(load_info->chunks->load_sum[0], loads[0]);
  EXPECT_EQ(load_info->chunks->load_sum[1], loads[1]);
  EXPECT_EQ(load_info->chunks->tasks[0].size(), 1);
  EXPECT_EQ(load_info->chunks->tasks[1].size(), 1);
}

TEST_F(PartitionChunksTest, partitionUnevenTasksTest) {
  chunk_size = 2;
  load_size = 5;

  initializeLoads(); // Loads are 5,4,3,2,1
  initializeLoadSetInfo();

  callTestFunction(); // Should chunk as (1,2,3,4) and (5)

  EXPECT_EQ(load_info->chunks->load_sum[0], 10);
  EXPECT_EQ(load_info->chunks->load_sum[1], 5);
  EXPECT_EQ(load_info->chunks->tasks[0].size(), 4);
  EXPECT_EQ(load_info->chunks->tasks[1].size(), 1);
}

TEST_F(PartitionChunksTest, moreChunksForUnevenTasks) {
  chunk_size = 3;
  load_size = 5;

  initializeLoads(); // Loads are 5,4,3,2,1
  initializeLoadSetInfo(); // Average is 5.

  callTestFunction(); // Should chunk as (1,2,3), (4,5) and ()

  EXPECT_EQ(load_info->chunks->load_sum[0], 6);
  EXPECT_EQ(load_info->chunks->load_sum[1], 9);
  EXPECT_EQ(load_info->chunks->tasks[0].size(), 3);
  EXPECT_EQ(load_info->chunks->tasks[1].size(), 2);
}

TEST_F(PartitionChunksTest, largerLoadsFirst) {
  chunk_size = 4;
  load_size = 10;

  initializeLoadsLargerFirst(); // Loads are 10,9,8,7,6,5,4,3,2,1
  initializeLoadSetInfo(); // Average is 14.

  callTestFunction(); // Should chunk as (10,9), (8,7), (6,5,4) and (3,2,1)

  EXPECT_EQ(load_info->chunks->load_sum[0], 19);
  EXPECT_EQ(load_info->chunks->load_sum[1], 15);
  EXPECT_EQ(load_info->chunks->load_sum[2], 15);
  EXPECT_EQ(load_info->chunks->load_sum[3], 6);

  EXPECT_EQ(load_info->chunks->tasks[0].size(), 2);
  EXPECT_EQ(load_info->chunks->tasks[1].size(), 2);
  EXPECT_EQ(load_info->chunks->tasks[2].size(), 3);
  EXPECT_EQ(load_info->chunks->tasks[3].size(), 3);
}

}