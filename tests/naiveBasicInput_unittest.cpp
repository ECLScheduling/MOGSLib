#include <gtest/gtest.h>
#include <lb/input/naiveBasicInput.h>

typedef NaiveBasicInput::Id Id;
typedef NaiveBasicInput::Load Load;

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
    input = new NaiveBasicInput(*peIds, *tasks);
  }
};

class EmptyNaiveBasicInputTest : public BasicFixtureForNaiveInputTests {
protected: 

  virtual void SetUp() {
    BasicFixtureForNaiveInputTests::SetUp();
    createInputObject();
  }

};

class NonEmptyNaiveBasicInputTest : public BasicFixtureForNaiveInputTests {
protected:

  Id anPEid = 0;

  void createInputWith1PE() {
    peIds->insert(anPEid);
    createInputObject();
  }
};

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
  createInputWith1PE();

  auto expected = 1;
  auto actual = input->getPEsIds().size();

  ASSERT_EQ(expected, actual) << "The input should contain " << expected << " PEs, but had " << actual << ".";
}