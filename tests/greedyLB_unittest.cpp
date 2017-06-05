#include <gtest/gtest.h>
#include <lb/impl/greedyLB.h>
#include <lb/input/naiveBasicInput.h>

/**
 * Fixture for testing the GreedyLB load balancing strategy.
 */
class GreedyLBTest : public ::testing::Test {
protected: 
  typedef NaiveBasicInput::SetOfId SetOfId;
  typedef NaiveBasicInput::LoadMap LoadMap;
  typedef NaiveBasicInput::Load Load;
  typedef NaiveBasicInput::Id Id;

  GreedyLB<NaiveBasicInput> loadBalancer;
  NaiveBasicInput *basicInput;
  MigrationElement output;

  LoadMap taskMap;
  SetOfId peSet;

  virtual void SetUp() {
  }

  virtual void tearDown() {
    if(basicInput != 0)
      delete basicInput;
  }

  void addTask(const Id &id, const Load &load) {
    taskMap[id] = load;
  }

  void addPE(const Id &id) {
    peSet.insert(id);
  }

  void createInput() {
    basicInput = new NaiveBasicInput(taskMap, peSet);
  }

  void work() {
    output = loadBalancer.work(*basicInput);  
  }
};

TEST_F(GreedyLBTest, emptyInput) {
  createInput();
  work();  

  EXPECT_EQ(0,output.count()) << "GreedyLB has been given an empty input and yet issued an output.";
}

TEST_F(GreedyLBTest, singleTaskSinglePE) {
  const Load taskLoad = 10;
  const Id id = 0;

  addTask(id, taskLoad);
  addPE(id);

  createInput();
  
  work();  

  ASSERT_EQ(1,output.count()); 
  EXPECT_EQ(taskLoad, loadBalancer.PEs.top().load) << "The Assigned PE has a different load than the informed input.";
  EXPECT_EQ(id, loadBalancer.PEs.top().id) << "The assigned PE has a different id than the informed input.";
}

TEST_F(GreedyLBTest, twoTasksSinglePE) {
  const Load task0Load = 10, task1Load = 20;
  const Id id0 = 0, id1 = 1;

  addTask(id0, task0Load);
  addTask(id1, task1Load);
  addPE(id0);

  createInput();
  
  work();  

  ASSERT_EQ(2,output.count()); 
  EXPECT_EQ(task0Load + task1Load, loadBalancer.PEs.top().load);
}

TEST_F(GreedyLBTest, oneTasksTwoPE) {
  const Load task0Load = 10;
  const Id id0 = 0, id1 = 1;

  addTask(id0, task0Load);
  addPE(id0);
  addPE(id1);

  createInput();
  
  work();  

  ASSERT_EQ(1,output.count()); 
  EXPECT_EQ(0, loadBalancer.PEs.top().load);

  loadBalancer.PEs.pop();

  EXPECT_EQ(task0Load, loadBalancer.PEs.top().load);
}

TEST_F(GreedyLBTest, twoTasksTwoPEs) {
  const Load lowerLoad = 10, greaterLoad = 20;
  const Id id0 = 0, id1 = 1;

  addTask(id0, lowerLoad);
  addTask(id1, greaterLoad);
  addPE(id0);
  addPE(id1);

  createInput();
  
  work();  

  ASSERT_EQ(2,output.count()); 
  EXPECT_EQ(lowerLoad, loadBalancer.PEs.top().load);

  loadBalancer.PEs.pop();

  EXPECT_EQ(greaterLoad, loadBalancer.PEs.top().load);
}