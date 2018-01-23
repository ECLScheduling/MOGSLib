#include <gtest/gtest.h>
#include <structures/binLPT/taskChunks.h>
#include <system/traits.h>

namespace BinLPT_Chunk_Test {

/**
 * This class is a helper class to test the BinLPT Chunk structure.
 */
class TaskChunkTest : public ::testing::Test {
public:

  using UInt = Traits<void>::UInt;
  using Load = Traits<void>::Load;

  using TaskChunks = BinLPT::TaskChunks<Load, UInt>;

  TaskChunks *chunks;
  Load loadA, loadB;

  void allocateChunks(const UInt &chunk_count) {
    chunks = new TaskChunks(chunk_count);
  }

  void TearDown() {
    delete chunks;
  }

};

TEST_F(TaskChunkTest, chunksAreCreatedEmpty) {
  allocateChunks(1);

  ASSERT_EQ(chunks->load_sum[0], 0);
  ASSERT_EQ(chunks->tasks[0].size(), 0);
}

TEST_F(TaskChunkTest, chunksRegisterTheAmountOfAddedTasks) {
  allocateChunks(1);
  chunks->addTask(0,0,1);

  ASSERT_EQ(chunks->tasks[0].size(), 1);
}

TEST_F(TaskChunkTest, chunksRegisterTheLoadSumOfAddedTasks) {
  loadA = 10;
  allocateChunks(1);
  chunks->addTask(0,0,loadA);

  ASSERT_EQ(chunks->load_sum[0], loadA);
}

TEST_F(TaskChunkTest, chunksRegisterTheLoadSumOfAllAddedTasks) {
  loadA = 10;
  loadB = 20;

  allocateChunks(1);
  chunks->addTask(0,0,loadA);
  chunks->addTask(0,1,loadB);

  ASSERT_EQ(chunks->tasks[0].size(), 2);
  ASSERT_EQ(chunks->load_sum[0], loadA + loadB);
}

TEST_F(TaskChunkTest, tasksToDifferentchunks) {
  loadA = 10;
  loadB = 20;

  allocateChunks(2);
  chunks->addTask(0,0,loadA);
  chunks->addTask(1,1,loadB);

  ASSERT_EQ(chunks->tasks[0].size(), 1);
  ASSERT_EQ(chunks->tasks[1].size(), 1);
  ASSERT_EQ(chunks->load_sum[0], loadA);
  ASSERT_EQ(chunks->load_sum[1], loadB);
}

}