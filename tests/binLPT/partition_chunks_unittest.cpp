#include <gtest/gtest.h>
#include <system/traits.h>
#include <algorithms/binLPT/binLPTAlgorithm.h>

namespace BinLPT_PartitionChunks_Test {

/**
 * This class is a helper class to test the BinLPT Partition Chunk function.
 */
class PartitionChunksTest : public ::testing::Test {
private:
  bool chunks_allocated, loads_allocated;

public:

  using UInt = Traits<void>::UInt;
  using Load = Traits<void>::Load;

  using Algorithms = BinLPT::Algorithms<Load, UInt>;
  using LoadSetInfo = BinLPT::LoadSetInfo<Load, UInt>;
  using TaskChunk = BinLPT::TaskChunk<Load, UInt>;

  /**
   * load info input that is used in the partitionChunks function.
   */
  LoadSetInfo load_info;

  /**
   * Array sizes for loads and chunks.
   */
  UInt load_size, chunk_size;

  /**
   * Array of load information to be referenced inside load_info.
   */
  Load *loads;

  /**
   * Array of chunks to be passed as a reference to the partitionChunks function.
   */
  TaskChunk *chunks;

  void allocChunks() {
    chunks = new TaskChunk[chunk_size];
    chunks_allocated = true;
  }

  void allocLoads() {
    loads = new Load[load_size];
    loads_allocated = true; 
  }

  void initializeLoads() {
    allocLoads();
    for(UInt i = 0; i < load_size; ++i) {
      loads[i] = i+1;
    }
  }

  void initializeLoadsLargerFirst() {
    allocLoads();
    for(UInt i = 0; i < load_size; ++i) {
      loads[i] = load_size-i;
    }
  }

  void initializeLoadSetInfo() {
    load_info = LoadSetInfo::analyzeLoadArray(loads, load_size, chunk_size);
  }

  void cleanLoads() {
    delete [] loads;
  }

  void cleanChunks() {
    delete [] chunks;
  }

  void SetUp() {
    chunks_allocated = 0;
    loads_allocated = 0;
    load_info = LoadSetInfo();
  }

  void TearDown() {
    if(chunks_allocated) {
      cleanChunks();
    }

    if(loads_allocated) {
      cleanLoads();
    }
  }

  void callTestFunction() {
    Algorithms::partitionChunks(load_info, chunks);  
  }

};

TEST_F(PartitionChunksTest, emptyLoadInfoShouldUseOneChunkWithNoTasks) {
  chunk_size = 1;
  allocChunks();

  callTestFunction();

  EXPECT_EQ(chunks[0].load_sum, 0);
  EXPECT_EQ(chunks[0].it_indice.size(), 0);
}

TEST_F(PartitionChunksTest, partitionSingleTaskTest) {
  chunk_size = 2;
  load_size = 1;

  allocChunks();
  initializeLoads();
  initializeLoadSetInfo();

  callTestFunction();

  EXPECT_EQ(chunks[0].load_sum, loads[0]);
  EXPECT_EQ(chunks[0].it_indice.size(), 1);
}

TEST_F(PartitionChunksTest, partitionTwoEqualTasksTest) {
  chunk_size = 2;
  load_size = 2;

  allocChunks();
  initializeLoads();
  loads[0] = 1;
  loads[1] = 1;
  initializeLoadSetInfo(); // Should chunk as (1) and (1)

  callTestFunction();

  EXPECT_EQ(chunks[0].load_sum, loads[0]);
  EXPECT_EQ(chunks[1].load_sum, loads[1]);
  EXPECT_EQ(chunks[0].it_indice.size(), 1);
  EXPECT_EQ(chunks[1].it_indice.size(), 1);
}

TEST_F(PartitionChunksTest, partitionUnevenTasksTest) {
  chunk_size = 2;
  load_size = 5;

  allocChunks();
  initializeLoads(); // Loads are 5,4,3,2,1
  initializeLoadSetInfo();

  callTestFunction(); // Should chunk as (1,2,3,4) and (5)

  EXPECT_EQ(chunks[0].load_sum, 10);
  EXPECT_EQ(chunks[1].load_sum, 5);
  EXPECT_EQ(chunks[0].it_indice.size(), 4);
  EXPECT_EQ(chunks[1].it_indice.size(), 1);
}

TEST_F(PartitionChunksTest, moreChunksForUnevenTasks) {
  chunk_size = 3;
  load_size = 5;

  allocChunks();
  initializeLoads(); // Loads are 5,4,3,2,1
  initializeLoadSetInfo(); // Average is 5.

  callTestFunction(); // Should chunk as (1,2,3), (4,5) and ()

  EXPECT_EQ(chunks[0].load_sum, 6);
  EXPECT_EQ(chunks[1].load_sum, 9);
  EXPECT_EQ(chunks[0].it_indice.size(), 3);
  EXPECT_EQ(chunks[1].it_indice.size(), 2);
}

TEST_F(PartitionChunksTest, largerLoadsFirst) {
  chunk_size = 4;
  load_size = 10;

  allocChunks();
  initializeLoadsLargerFirst(); // Loads are 10,9,8,7,6,5,4,3,2,1
  initializeLoadSetInfo(); // Average is 14.

  callTestFunction(); // Should chunk as (10,9), (8,7), (6,5,4) and (3,2,1)

  EXPECT_EQ(chunks[0].load_sum, 19);
  EXPECT_EQ(chunks[1].load_sum, 15);
  EXPECT_EQ(chunks[2].load_sum, 15);
  EXPECT_EQ(chunks[3].load_sum, 6);

  EXPECT_EQ(chunks[0].it_indice.size(), 2);
  EXPECT_EQ(chunks[1].it_indice.size(), 2);
  EXPECT_EQ(chunks[2].it_indice.size(), 3);
  EXPECT_EQ(chunks[3].it_indice.size(), 3);
}

}