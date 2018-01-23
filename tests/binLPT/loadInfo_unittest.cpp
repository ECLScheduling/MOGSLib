#include <gtest/gtest.h>
#include <structures/binLPT/loadsetInfo.h>
#include <system/traits.h>

namespace BinLPT_LoadInfo_Test {

/**
 * This class is a helper class to test the BinLPT LoadInfo structure.
 */
class LoadSetInfoTest : public ::testing::Test {
public:

  using UInt = Traits<void>::UInt;
  using Load = Traits<void>::Load;

  using LoadSetInfo = BinLPT::LoadSetInfo<Load, UInt>;

  LoadSetInfo *load_info;
  std::vector<Load> loads;
  UInt loads_size;
  UInt chunk_amount;

  void initializeLoadsWithIncreasingValues(const UInt &amount = 1) {
    for(UInt i = 0; i < amount; ++i) {
      loads.push_back(i+1);
    }
  }

  void TearDown() {
    loads.clear();
  }
};

TEST_F(LoadSetInfoTest, LoadInfoAreCreatedEmpty) {
  load_info = new LoadSetInfo();

  ASSERT_EQ(load_info->load_sum, 0);
  ASSERT_EQ(load_info->load_avg, 0);
  ASSERT_EQ(load_info->load_max, 0);
  ASSERT_EQ(load_info->loads, nullptr);
}

TEST_F(LoadSetInfoTest, AnalysisTest) {
  const UInt &amount_of_tasks = 5;
  const UInt chunk_amount = 3;

  // Create the loads dataset
  initializeLoadsWithIncreasingValues(amount_of_tasks);
  const Load &expected_load_sum = 5+4+3+2+1;

  // Initialize the structure
  load_info = LoadSetInfo::analyzeLoadArray(loads, chunk_amount);

  ASSERT_EQ(load_info->load_sum, expected_load_sum);
  ASSERT_EQ(load_info->load_avg, expected_load_sum/chunk_amount);
  ASSERT_EQ(load_info->load_max, 5);
  ASSERT_EQ(load_info->loads->size(), amount_of_tasks);
  ASSERT_EQ(load_info->chunks->size, chunk_amount);
}

TEST_F(LoadSetInfoTest, AnalysisTestUnorderedValues) {
  const UInt &amount_of_tasks = 6;
  const UInt chunk_amount = 4;
  const Load &expected_load_sum = 6+5+4+3+2+1;

  // Create the loads dataset
  loads = std::vector<Load>(amount_of_tasks);
  loads[0] = 2;
  loads[1] = 4;
  loads[2] = 3;
  loads[3] = 6;
  loads[4] = 5;
  loads[5] = 1;

  // Initialize the structure
  load_info = LoadSetInfo::analyzeLoadArray(loads, chunk_amount);

  ASSERT_EQ(load_info->load_sum, expected_load_sum);
  ASSERT_EQ(load_info->load_avg, expected_load_sum/chunk_amount);
  ASSERT_EQ(load_info->load_max, 6);
  ASSERT_EQ(load_info->loads->size(), amount_of_tasks);
  ASSERT_EQ(load_info->chunks->size, chunk_amount);
}

}