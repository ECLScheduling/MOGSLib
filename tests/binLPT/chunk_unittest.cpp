#include <gtest/gtest.h>
#include <algorithms/binLPT/binLPTAlgorithm.h>
#include <system/traits.h>

namespace BinLPT_Chunk_Test {

/**
 * This class is a helper class to test the BinLPT Chunk structure.
 */
class TaskChunkTest : public ::testing::Test {
public:

  using UInt = Traits<void>::UInt;
  using Load = Traits<void>::Load;

  using TaskChunk = BinLPT::TaskChunk<Load, UInt>;

  TaskChunk chunkA, chunkB;
  Load loadA, loadB;
};

TEST_F(TaskChunkTest, chunksAreCreatedEmpty) {
  ASSERT_EQ(chunkA.load_sum, 0);
  ASSERT_EQ(chunkA.it_indice.size(), 0);
}

TEST_F(TaskChunkTest, chunksRegisterTheAmountOfAddedTasks) {
  chunkA.addTask(0,0);

  ASSERT_EQ(chunkA.it_indice.size(), 1);
}

TEST_F(TaskChunkTest, chunksRegisterTheLoadSumOfAddedTasks) {
  loadA = 10;

  chunkA.addTask(0, loadA);

  ASSERT_EQ(chunkA.load_sum, loadA);
}

TEST_F(TaskChunkTest, chunksRegisterTheLoadSumOfAllAddedTasks) {
  loadA = 10;
  loadB = 20;

  chunkA.addTask(0, loadA);
  chunkA.addTask(1, loadB);

  ASSERT_EQ(chunkA.it_indice.size(), 2);
  ASSERT_EQ(chunkA.load_sum, loadA + loadB);
}

TEST_F(TaskChunkTest, operatorGreaterThan) {
  loadA = 10;
  loadB = 20;

  chunkA.addTask(0, loadA);
  chunkB.addTask(1, loadB);

  ASSERT_TRUE(chunkB > chunkA);
}

TEST_F(TaskChunkTest, operatorLessThan) {
  loadA = 10;
  loadB = 20;

  chunkA.addTask(0, loadA);
  chunkB.addTask(1, loadB);

  ASSERT_FALSE(chunkB < chunkA);
}

}