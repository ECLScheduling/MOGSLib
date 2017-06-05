#include <gtest/gtest.h>
#include <lb/input/naiveBasicInputInitialLoad.h>

typedef NaiveBasicInputInitialLoad::Id Id;
typedef NaiveBasicInputInitialLoad::Load Load;
typedef NaiveBasicInputInitialLoad::LoadMap LoadMap;
typedef NaiveBasicInputInitialLoad::SetOfId SetOfId;

/**
 * This test fixture is used to test the extension methods of the class NaiveInputInitialLoad, from its basic counterpart NaiveBasicInput.
 */
class NaiveBasicInputInitialLoadTests : public ::testing::Test {
protected: 
  
  NaiveBasicInputInitialLoad *input;
  LoadMap *pes;
  LoadMap *tasks;

  virtual void SetUp() {
    pes = new LoadMap();
    tasks = new LoadMap();
  }

  virtual void TearDown() {
    delete pes;
    delete tasks;
    delete input;
  }

  void createInputObject() {
    input = new NaiveBasicInputInitialLoad(*tasks, *pes);
  }

  void addPE(const Id &id, const Load &load) {
    (*pes)[id] = load;
  }

};

TEST_F(NaiveBasicInputInitialLoadTests, shouldReturnAnEmptyPEIdSet) {
  createInputObject();

  auto expected = 0;
  auto actual = input->getPEsIds().size();

  ASSERT_EQ(expected, actual) << "Size of PE id set should be " << expected << " but was " << actual;
}

TEST_F(NaiveBasicInputInitialLoadTests, shouldReturnAnNonEmptyPEIdSet) {
  const Id id = 0;
  const Load load = 10;

  addPE(id, load);
  addPE(id+1, load);
  createInputObject();

  auto expected = 2;
  auto actual = input->getPEsIds().size();

  ASSERT_EQ(expected, actual) << "Size of PE id set should be " << expected << " but was " << actual;
}

TEST_F(NaiveBasicInputInitialLoadTests, shouldReturnTheCorrectLoadWhenOnlyOnePE) {
  const Id id = 0;
  const Load load = 10;

  addPE(id, load);
  createInputObject();

  auto expected = load;
  auto actual = input->getPELoad(id);

  ASSERT_EQ(expected, actual) << "PE load should be " << expected << " but was " << actual;
}

TEST_F(NaiveBasicInputInitialLoadTests, shouldReturnTheCorrectLoadWhenMoreThanOnePE) {
  const Id id0 = 0, id1 = 1;
  const Load load0 = 10, load1 = 20;

  addPE(id1, load1);
  addPE(id0, load0);
  createInputObject();

  auto expected = load0;
  auto actual = input->getPELoad(id0);

  EXPECT_EQ(expected, actual) << "PE " << id0 << " load should be " << expected << " but was " << actual;

  expected = load1;
  actual = input->getPELoad(id1);

  ASSERT_EQ(expected, actual) << "PE " << id1 << " load should be " << expected << " but was " << actual;
}