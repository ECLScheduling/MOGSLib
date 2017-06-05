#include <gtest/gtest.h>
#include <lb/input/naiveBasicInput.h>

typedef NaiveBasicInput::Id Id;
typedef NaiveBasicInput::Load Load;

/**
 * This test fixture is for declaring the common structures between the NaiveBasicInput's test fixtures.
 */
class BasicFixtureForNaiveInputTests : public ::testing::Test {
protected: 
  
  NaiveBasicInput *input;
  std::set<Id> *peIds;
  std::map<Id, Load> *tasks;

  virtual void SetUp() {
    peIds = new std::set<Id>();
    tasks = new std::map<Id, Load>();
  }

  virtual void TearDown() {
    delete peIds;
    delete tasks;
    delete input;
  }

  void createInputObject() {
    input = new NaiveBasicInput(*tasks, *peIds);
  }
};


/**
 * This test fixture is for testing the NaiveBasicInput when it is empty. This fixture is not meant to stress test the input class.
 */
class EmptyNaiveBasicInputTest : public BasicFixtureForNaiveInputTests {
protected: 

  virtual void SetUp() {
    BasicFixtureForNaiveInputTests::SetUp();
    createInputObject();
  }

};


/**
 * This test fixture is for testing the NaiveBasicInput most simple features in the system. This fixture is not meant to stress test the input class.
 */
class NonEmptyNaiveBasicInputTest : public BasicFixtureForNaiveInputTests {
protected:
  static const Load defaultTaskLoad = 10;
  Id taskId;
  Id peId;

  virtual void SetUp() {
    BasicFixtureForNaiveInputTests::SetUp();
    taskId = 0;
    peId = 0;
  }

  void addTask(const Load &aTaskLoad = NonEmptyNaiveBasicInputTest::defaultTaskLoad) {
    (*tasks)[taskId++] = aTaskLoad;
  }

  void addPE() {
    peIds->insert(peId++);
  }
};

// Re-declaration of this static fixture variable so it can be seen by the compiler.
const Load NonEmptyNaiveBasicInputTest::defaultTaskLoad;

TEST_F(EmptyNaiveBasicInputTest, shouldReturnAnEmptySetOfTaskIds) {

  auto expected = 0;
  auto actual = input->getTasksIds().size();
  ASSERT_EQ(expected, actual) << "An Empty Input should have " << expected << " tasks, but had " << actual << ".";
}

TEST_F(EmptyNaiveBasicInputTest, shouldReturnAnEmptySetOfPEsIds) {

  auto expected = 0;
  auto actual = input->getPEsIds().size();
  ASSERT_EQ(expected, actual) << "An Empty Input should have " << expected << " PEs, but had " << actual << ".";
}

TEST_F(EmptyNaiveBasicInputTest, shouldThrowExceptionWhenTryingToFetchATaskLoad) {

  ASSERT_THROW(input->getTaskLoad(0), std::string) << "Attempted to access a non-existent task load and succeded.";
}

TEST_F(NonEmptyNaiveBasicInputTest, shouldContain1PEWhenTheSetOfPEsHasSize1) {

  addPE();
  createInputObject();

  auto expected = 1;
  auto actual = input->getPEsIds().size();

  ASSERT_EQ(expected, actual) << "The input should contain " << expected << " PEs, but had " << actual << ".";

}

TEST_F(NonEmptyNaiveBasicInputTest, shouldContain1TaskIfTaskSetHasSize1) {
  addTask();
  createInputObject();

  auto expected = 1;
  auto actual = input->getTasksIds().size();

  ASSERT_EQ(expected, actual) << "The input should contain " << expected << " Tasks, but had " << actual << ".";
}

TEST_F(NonEmptyNaiveBasicInputTest, shouldContain1TaskAnd1PEIfInputHas1TaskAnd1PE) {
  addTask();
  addPE();
  createInputObject();

  auto expected = 1;
  auto taskCount = input->getTasksIds().size();
  auto peCount = input->getPEsIds().size();

  ASSERT_EQ(expected, taskCount) << "The input should contain " << expected << " Tasks, but had " << taskCount << ".";
  ASSERT_EQ(expected, peCount) << "The input should contain " << expected << " PEs, but had " << peCount << ".";
}

TEST_F(NonEmptyNaiveBasicInputTest, shouldContainAnArbitraryNumberOfPEsAndTasks) {
  const unsigned int anyNumber = 5;
  const unsigned int anyOtherNumber = 9;

  for(unsigned int i = 0; i <  anyNumber; ++i)
    addTask();
  for(unsigned int i = 0; i <  anyOtherNumber; ++i)
    addPE();

  createInputObject();

  auto taskCount = input->getTasksIds().size();
  auto peCount = input->getPEsIds().size();

  ASSERT_EQ(anyNumber, taskCount) << "The input should contain " << anyNumber << " Tasks, but had " << taskCount << ".";
  ASSERT_EQ(anyOtherNumber, peCount) << "The input should contain " << anyOtherNumber << " PEs, but had " << peCount << ".";
}

TEST_F(NonEmptyNaiveBasicInputTest, shouldRetrieveTheCorrectTaskLoad) {
  const Load load0 = 10;
  const Load load1 = 15;

  addTask(load0);
  addTask(load1);
  createInputObject();

  const Load actualLoad0 = input->getTaskLoad(0);
  const Load actualLoad1 = input->getTaskLoad(1);

  ASSERT_EQ(load0, actualLoad0) << "Task 0 expected to hade load " << load0 << " but had load " << actualLoad0 << ".";
  ASSERT_EQ(load1, actualLoad1) << "Task 1 expected to hade load " << load1 << " but had load " << actualLoad1 << ".";
}