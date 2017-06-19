#include <gtest/gtest.h>
#include <strategies/migrationElement.h>

class MigrationElementTest : public ::testing::Test {
protected: 
  MigrationElement migrationElement;

  virtual void SetUp() {}

  virtual void tearDown() {}

  const MigrationElement::Id anId() {
    return 0;
  }

  const MigrationElement::Id anotherId() {
    return 2;
  }

  const MigrationElement::Id invalidId() {
    return 1;
  }

  void setAMigrationInTheElement() {
    migrationElement.set(anId(), anId());
  }

};

class MigrationElementTestAfterAddition : public MigrationElementTest {
protected: 

  virtual void SetUp() {
    setAMigrationInTheElement();
  }

};

TEST_F(MigrationElementTest, hasNoMigrationsInitially) {
  
  auto count = migrationElement.count();
  auto expected = 0;

  EXPECT_EQ(expected,count) << "Migration element should be initialized with " << expected << " elements, but was " << count << ".";
}

TEST_F(MigrationElementTestAfterAddition, hasOneMigrationAfterAddition) {
  
  auto count = migrationElement.count();
  auto expected = 1;
  ASSERT_EQ(expected, count) << "Migration element should have " << expected << "migrations, but had " << count << ".";
}

TEST_F(MigrationElementTest, willThrowIfPEIsAccessedInAnInvalidId) {

  ASSERT_THROW(migrationElement.getTaskPE(invalidId()), std::string) << "Acessed a PE of a Task that shouldn't be mapped for migration.";
}

TEST_F(MigrationElementTestAfterAddition, willNotThrowIfPEIsAccessedInAValidId) {

  ASSERT_NO_THROW(migrationElement.getTaskPE(anId())) << "Acessed a PE of a valid mapped Task for migration, but got an exception.";
}

TEST_F(MigrationElementTestAfterAddition, willRetrieveTheCorrectPeIdOfTheMappedMigration) {
 
  auto should = anId();
  auto actual = migrationElement.getTaskPE(anId());
  ASSERT_EQ(should, actual) << "The task's PE should be " << should << " but was " << actual << "."; 
}

TEST_F(MigrationElementTest, shouldNotHaveAnyTaskMappedInitially) {

  auto expected = 0;
  auto current = migrationElement.mappedTasks().size();

  ASSERT_EQ(expected, current) << "Mapped Tasks for migration should be " << expected << " after element creation, but was " << current << ".";
}

TEST_F(MigrationElementTestAfterAddition, shouldHaveOneTaskMappedAfterAddition) {

  auto expected = 1;
  auto current = migrationElement.mappedTasks().size();

  ASSERT_EQ(expected, current) << "Mapped Tasks for migration should be " << expected << " after migration addition, but was " << current << ".";
}

TEST_F(MigrationElementTestAfterAddition, shouldHaveTheCorrectNumberOfTasksMappedAfterAdditions) {

  auto expected = 2;

  migrationElement.set(anotherId(), anotherId());

  auto current = migrationElement.mappedTasks().size();

  ASSERT_EQ(expected, current) << "Mapped Tasks for migration should be " << expected << " after migration addition, but was " << current << ".";
}