#include <gtest/gtest.h>

#include <policies/binlpt.h>

using Load = MOGSLib::Load;
using Index = MOGSLib::Index;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

using SchedulingPolicy = MOGSLib::Policy::BinLPT<Load>;

class BinlptPolicyTests : public ::testing::Test {
public:
  Index ntasks;
  Load *workloads;

  Index nPEs;
  Load *PE_workloads;

  Index k;

  TaskMap map;

  void execute_policy() {
    SchedulingPolicy::map(map, ntasks, workloads, nPEs, PE_workloads, k);
  }

  Load *call_cummulativesum() {
    return SchedulingPolicy::compute_cummulativesum<Load>(workloads, ntasks);
  }

  Index *call_compute_chunksizes() {
    return SchedulingPolicy::compute_chunksizes(ntasks, workloads, k);
  }

  Load *call_compute_chunkloads() {
    auto chunk_sizes = call_compute_chunksizes();
    auto out =  SchedulingPolicy::compute_chunkloads(ntasks, workloads, chunk_sizes, k);
    
    delete [] chunk_sizes;
    return out;
  }

  void createMap(const Index &n) {
    ntasks = n;
    workloads = new Load[ntasks]();
    map = new TaskEntry[ntasks]();
  }

  void setPEs(const Index &n) {
    nPEs = n;
    PE_workloads = new Load[nPEs]();
  }

  void SetUp() {
    ntasks = 0;
    nPEs = 0;
    k = 0;

    map = nullptr;
    workloads = nullptr;
    PE_workloads = nullptr;
  }

  void TearDown() {
    if(map != nullptr) {
      delete [] map;
      map = nullptr;
    }
    if(workloads != nullptr) {
      delete [] workloads;
      workloads = nullptr;
    }
    if(PE_workloads != nullptr) {
      delete [] PE_workloads;
      PE_workloads = nullptr;
    }
  }

  void set_regular_loads(const Index &n, const Load &load = 2) {
    createMap(n);
    for(Index i = 0; i < ntasks; ++i)
      workloads[i] = load;
  }

  void set_increasing_loads(const Index &n) {
    createMap(n);
    for(Index i = 0; i < ntasks; ++i)
      workloads[i] = i+1;
  }

  void set_decreasing_loads(const Index &n) {
    createMap(n);
    for(Index i = 0; i < ntasks; ++i)
      workloads[i] = ntasks-i;
  }

};

TEST_F(BinlptPolicyTests, compute_cummulative_sum_one) {
  createMap(1);

  auto out = call_cummulativesum();

  ASSERT_EQ(0, out[0]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, compute_cummulative_sum_two) {
  createMap(2);

  workloads[0] = 3;
  workloads[1] = 2;

  auto out = call_cummulativesum();

  ASSERT_EQ(0, out[0]);
  ASSERT_EQ(workloads[0], out[1]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, compute_cummulative_sum_n) {
  createMap(3);

  workloads[0] = 3;
  workloads[1] = 2;
  workloads[2] = 4;

  auto out = call_cummulativesum();

  ASSERT_EQ(0, out[0]);
  ASSERT_EQ(workloads[0], out[1]);
  ASSERT_EQ(workloads[0] + workloads[1], out[2]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, chunksizes_one_chunk) {
  createMap(3);
  k = 1;

  auto out = call_compute_chunksizes();

  ASSERT_EQ(3, out[0]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, chunksizes_two_chunks_regular_loads) {
  k = 2;
  set_regular_loads(4);

  auto out = call_compute_chunksizes();

  ASSERT_EQ(2, out[0]);
  ASSERT_EQ(2, out[1]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, chunksizes_two_chunks_irregular_loads) {
  k = 2;
  set_increasing_loads(4); // [1,2,3,4] => ([1,2,3] , [4])

  auto out = call_compute_chunksizes();

  ASSERT_EQ(3, out[0]);
  ASSERT_EQ(1, out[1]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, chunksizes_two_chunks_irregular_loads_locality_grouping) {
  k = 2;
  set_decreasing_loads(4); // [4,3,2,1] => ([4,3] , [2,1])

  auto out = call_compute_chunksizes();

  ASSERT_EQ(2, out[0]);
  ASSERT_EQ(2, out[1]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, chunksizes_non_exact_division) {
  k = 4;
  set_decreasing_loads(5); // [5,4,3,2,1]

  auto out = call_compute_chunksizes();
  
  /** 
   * mean load/chunk = 15/4 = 4
   * [5] [4] [3,2] [1]
   **/

  ASSERT_EQ(1, out[0]);
  ASSERT_EQ(1, out[1]);
  ASSERT_EQ(2, out[2]);
  ASSERT_EQ(1, out[3]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, chunkloads_regular) {
  Load avg_load = 5;
  Index tasks = 4;

  k = 2;

  set_regular_loads(tasks, avg_load);
  auto out = call_compute_chunkloads();

  auto expected_load = avg_load*tasks/k;
  for(Index i = 0; i < k; ++i)
    ASSERT_EQ(expected_load, out[i]);
  delete [] out;
}

TEST_F(BinlptPolicyTests, chunkloads_irregular) {
  Index tasks = 4;

  k = 2;

  set_increasing_loads(tasks); // [1,2,3,4]
  auto out = call_compute_chunkloads(); // [1,2,3] , [4]

  ASSERT_EQ(6, out[0]);
  ASSERT_EQ(4, out[1]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, chunkloads_decreasing_irregular) {
  Index tasks = 5;
  k = 4;

  set_decreasing_loads(tasks); // [5,4,3,2,1]
  auto out = call_compute_chunkloads(); // [5] , [4] , [3,2] , [1]

  ASSERT_EQ(5, out[0]);
  ASSERT_EQ(4, out[1]);
  ASSERT_EQ(5, out[2]);
  ASSERT_EQ(1, out[3]);

  delete [] out;
}

TEST_F(BinlptPolicyTests, policy_regular_tasks_unloaded_PEs) {
  Index tasks = 4;
  Index PEs = 2;
  k = 2;

  set_regular_loads(tasks, 5); // [5,5,5,5] => 0:[5,5] 1:[5,5] => assign order:{0,1}
  setPEs(PEs);

  execute_policy();

  EXPECT_EQ(1, map[0]);
  EXPECT_EQ(1, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(0, map[3]);
}

TEST_F(BinlptPolicyTests, policy_irregular_tasks_unloaded_PEs) {
  Index tasks = 5;
  Index PEs = 2;
  k = 2;

  set_increasing_loads(tasks); // [1,2,3,4,5] => 0:[1,2,3,4] 1:[5] => assign order:{0,1}
  setPEs(PEs);

  execute_policy();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(0, map[2]);
  EXPECT_EQ(0, map[3]);
  EXPECT_EQ(1, map[4]);
}

TEST_F(BinlptPolicyTests, policy_irregular_tasks_decreasing_unloaded_PEs) {
  Index tasks = 5;
  Index PEs = 2;
  k = 4;

  set_decreasing_loads(tasks); // [5,4,3,2,1] => 0:[5] 1:[4] 2:[3,2] 3:[1] => ordered:{0,2,1,3}
  setPEs(PEs);

  execute_policy();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}

TEST_F(BinlptPolicyTests, policy_regular_tasks_loaded_PEs) {
  Index tasks = 4;
  Index PEs = 2;
  k = 2;

  set_regular_loads(tasks, 5); // [5,5,5,5] => 0:[5,1] 1:[5,5] => ordered:{0,1}
  
  setPEs(PEs);
  PE_workloads[0] = 7;

  execute_policy();

  EXPECT_EQ(0, map[0]);
  EXPECT_EQ(0, map[1]);
  EXPECT_EQ(1, map[2]);
  EXPECT_EQ(1, map[3]);
}

TEST_F(BinlptPolicyTests, policy_irregular_tasks_loaded_PEs) {
  Index tasks = 5;
  Index PEs = 4;
  k = 3;

  set_increasing_loads(tasks); // [1,2,3,4,5] => 0:[1,2,3] 1:[4,5] 2:[] => ordered:{0,1}
  
  setPEs(PEs);
  PE_workloads[0] = 7;

  execute_policy();

  EXPECT_EQ(2, map[0]);
  EXPECT_EQ(2, map[1]);
  EXPECT_EQ(2, map[2]);
  EXPECT_EQ(1, map[3]);
  EXPECT_EQ(1, map[4]);
}