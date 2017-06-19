#include <gtest/gtest.h>
#include <strategies/impl/greedy/greedyStrategyInitialLoad.h>
#include <strategies/input/naiveBasicInputInitialLoad.h>

// ###########################################
// Tests using the GreedyStrategyTest Fixture.
// ###########################################

/**
 * Fixture for testing the GreedyLB load balancing strategy.
 */
class GreedyStrategyTest : public ::testing::Test {
protected: 
  typedef NaiveBasicInput::SetOfId SetOfId;
  typedef NaiveBasicInput::LoadMap LoadMap;
  typedef NaiveBasicInput::Load Load;
  typedef NaiveBasicInput::Id Id;

  GreedyStrategy<NaiveBasicInput> loadBalancer;
  NaiveBasicInput *basicInput;
  MigrationElement output;

  LoadMap taskMap;
  SetOfId PESet;

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
    PESet.insert(id);
  }

  void createInput() {
    basicInput = new NaiveBasicInput(taskMap, PESet);
  }

  void work() {
    output = loadBalancer.mapTasks(*basicInput);  
  }
};

TEST_F(GreedyStrategyTest, emptyInput) {
  createInput();
  work();  

  EXPECT_EQ(0,output.count()) << "GreedyLB has been given an empty input and yet issued an output.";
}

TEST_F(GreedyStrategyTest, singleTaskSinglePE) {
  const Load taskLoad = 10;
  const Id id = 0;

  addTask(id, taskLoad);
  addPE(id);

  createInput();
  
  work();  

  ASSERT_EQ(1, output.count()); 
  EXPECT_EQ(taskLoad, loadBalancer.PEs.top().load) << "The Assigned PE has a different load than the informed input.";
  EXPECT_EQ(id, loadBalancer.PEs.top().id) << "The assigned PE has a different id than the informed input.";
}

TEST_F(GreedyStrategyTest, twoTasksSinglePE) {
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

TEST_F(GreedyStrategyTest, oneTasksTwoPE) {
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

TEST_F(GreedyStrategyTest, twoTasksTwoPEs) {
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

// ######################################################
// Tests using the GreedyInitialLoadStrategyTest Fixture.
// ######################################################

/**
 * Fixture for tests with the GreedyStrategy that uses a starting load on each PE, the GreedyInitialLoadStrategy.
 */
class GreedyInitialLoadStrategyTest : public ::testing::Test {
protected:
  typedef NaiveBasicInput::SetOfId SetOfId;
  typedef NaiveBasicInput::LoadMap LoadMap;
  typedef NaiveBasicInput::Load Load;
  typedef NaiveBasicInput::Id Id;

  GreedyInitialLoadStrategy<NaiveBasicInputInitialLoad> loadBalancer;
  NaiveBasicInputInitialLoad *input;
  MigrationElement output;

  LoadMap tasks;
  LoadMap PEs;

  virtual void SetUp() {
  }

  virtual void tearDown() {
    if(input != 0)
      delete input;
  }

  void addTask(const Id &id, const Load &load) {
    tasks[id] = load;
  }

  void addPE(const Id &id, const Load &load) {
    PEs[id] = load;
  }

  void createInput() {
    input = new NaiveBasicInputInitialLoad(tasks, PEs);
  }

  void work() {
    output = loadBalancer.mapTasks(*input);  
  }

};

TEST_F(GreedyInitialLoadStrategyTest, shouldStartThePELoadsCorrectly) {
  const Id id0 = 0, id1 = 1;
  const Load load0 = 10, load1 = 20;

  addPE(id0, load0);
  addPE(id1, load1);

  createInput();
  work();

  auto expectedId = id0;
  auto expectedLoad = load0;

  EXPECT_EQ(expectedId,loadBalancer.PEs.top().id);
  EXPECT_EQ(expectedLoad,loadBalancer.PEs.top().load); 

  loadBalancer.PEs.pop();
  expectedId = id1;
  expectedLoad = load1;

  EXPECT_EQ(expectedId,loadBalancer.PEs.top().id);
  EXPECT_EQ(expectedLoad,loadBalancer.PEs.top().load); 
}

TEST_F(GreedyInitialLoadStrategyTest, shouldWorkAsTheGreedyStrategy) {
  const Id id0 = 0, id1 = 1;
  const Load load0 = 10, load1 = 20;

  const Id taskId0 = 0;
  const Load taskLoad0 = 5;

  addPE(id0, load0);
  addPE(id1, load1);
  addTask(taskId0, taskLoad0);

  createInput();
  work();

  auto expectedId = id0;
  auto expectedLoad = load0 + taskLoad0;

  EXPECT_EQ(expectedId,loadBalancer.PEs.top().id);
  EXPECT_EQ(expectedLoad,loadBalancer.PEs.top().load); 

  loadBalancer.PEs.pop();
  expectedId = id1;
  expectedLoad = load1;

  EXPECT_EQ(expectedId,loadBalancer.PEs.top().id);
  EXPECT_EQ(expectedLoad,loadBalancer.PEs.top().load); 
}