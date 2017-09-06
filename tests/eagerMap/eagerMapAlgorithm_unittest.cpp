#include "fixtures/algorithmFixtures.h"

namespace EagerMapCommunicationTests {

// ###############################
// Tests using the CreateCommunicationMatrixTest Fixture
// ###############################

TEST_F(CreateCommunicationMatrixTest, simpleCase) {
  createRegularGroupOn3LevelsWith4Tasks();
  recreateCommunicationMatrix();

  /* Expected Communication Matrix Output
   *
   * | 0 14 |
   * | 14 0 |
   */
  ASSERT_EQ(0, commMatrix->at(0,0));
  ASSERT_EQ(0, commMatrix->at(1,1));  
  ASSERT_EQ(14, commMatrix->at(0,1));
  ASSERT_EQ(14, commMatrix->at(1,0));
}

TEST_F(CreateCommunicationMatrixTest, createCommunicationMatrix_irregularGroups) {
  createIrregularGroupOn3LevelsWith4Tasks();
  recreateCommunicationMatrix();

  /* Expected Communication Matrix Output
   *
   * | 0 6 8 |
   * | 6 0 6 |
   * | 8 6 0 |
   */
  ASSERT_EQ(0, commMatrix->at(0,0));
  ASSERT_EQ(0, commMatrix->at(1,1));
  ASSERT_EQ(0, commMatrix->at(2,2));
  
  ASSERT_EQ(6, commMatrix->at(0,1));
  ASSERT_EQ(6, commMatrix->at(1,0));
  ASSERT_EQ(8, commMatrix->at(0,2));
  ASSERT_EQ(8, commMatrix->at(2,0));
  ASSERT_EQ(6, commMatrix->at(1,2));
  ASSERT_EQ(6, commMatrix->at(2,1));
}

// ###############################
// Tests using the CreateGroupTests Fixture
// ###############################

/**
 * This tests checks wether a simple case of groups of size 2 would function. This is the base case since the for-loop will be iterated only once.
 */
TEST_F(CreateGroupTests, simpleCase) {
  expectedGroupSize = 2;
  expectedGroupTasksIds = new Index[expectedGroupSize];
  expectedGroupTasksIds[0] = 3;
  expectedGroupTasksIds[1] = 2;

  createDefaultRootGroup();
  generateGroup();

  //for(Index i = 0; i < order; ++i)
    //for(Index j = 0; j < order; ++j)
      //std::cout << commMatrix->

  ASSERT_EQ(expectedGroupSize, resultingGroup->nElements());
  for(Index i = 0; i < expectedGroupSize; ++i) {
    ASSERT_EQ(expectedGroupTasksIds[i], resultingGroup->elementAt(i)->id);  
  }
}

/**
 * This tests checks wether the regular case of groups of size of at least n-1 size would function. This is the inductive test, since the loop will iterate more than once.
 */
TEST_F(CreateGroupTests, regularCase) {
  expectedGroupSize = 3;
  expectedGroupTasksIds = new Index[expectedGroupSize];
  expectedGroupTasksIds[0] = 3;
  expectedGroupTasksIds[1] = 2;
  expectedGroupTasksIds[2] = 1;

  createDefaultRootGroup();
  generateGroup();

  ASSERT_EQ(expectedGroupSize, resultingGroup->nElements());
  for(Index i = 0; i < expectedGroupSize; ++i) {
    ASSERT_EQ(expectedGroupTasksIds[i], resultingGroup->elementAt(i)->id);  
  }
}

/**
 * This tests checks if the case where the group size is the same as the ammount of groups works.
 */
TEST_F(CreateGroupTests, maxSizeGroup) {
  expectedGroupSize = 4;
  expectedGroupTasksIds = new Index[expectedGroupSize];
  expectedGroupTasksIds[0] = 3;
  expectedGroupTasksIds[1] = 2;
  expectedGroupTasksIds[2] = 1;
  expectedGroupTasksIds[3] = 0;

  createDefaultRootGroup();
  generateGroup();

  ASSERT_EQ(expectedGroupSize, resultingGroup->nElements());
  for(Index i = 0; i < expectedGroupSize; ++i) {
    ASSERT_EQ(expectedGroupTasksIds[i], resultingGroup->elementAt(i)->id);  
  }
}

/**
 * This tests checks if the case where the group size is 1 works. The result should be the group with the maximum communication value
 */
TEST_F(CreateGroupTests, minSizeGroup) {
  expectedGroupSize = 1;
  expectedGroupTasksIds = new Index[expectedGroupSize];
  expectedGroupTasksIds[0] = 3;

  createDefaultRootGroup();
  generateGroup();

  ASSERT_EQ(expectedGroupSize, resultingGroup->nElements());
  for(Index i = 0; i < expectedGroupSize; ++i) {
    ASSERT_EQ(expectedGroupTasksIds[i], resultingGroup->elementAt(i)->id);  
  }
}

/**
 * This test exists to keep the algorithm simple. If it ever fails, the code has become unnecessary complex.
 * @details The task groups will be created inside the Algorithm's structures by the algorithm itself. \
 * The algorithm must, to maintain itself simple, always identify the groups with an increasing id, so it can map to the Communication Matrix in a direct manner, without using maps or further checks.
 */
TEST_F(CreateGroupTests, unorderedTasksWontWork) {
  expectedGroupSize = 2;
  expectedGroupTasksIds = new Index[expectedGroupSize];
  expectedGroupTasksIds[0] = 3;
  expectedGroupTasksIds[1] = 2;

  createUnorderedRootGroup();
  generateGroup();

  ASSERT_EQ(expectedGroupSize, resultingGroup->nElements());
  for(Index i = 0; i < expectedGroupSize; ++i) {
    ASSERT_FALSE(expectedGroupTasksIds[i] == resultingGroup->elementAt(i)->id);  
  }
}

TEST_F(CreateGroupTests, chosenArrayInitialized) {
  expectedGroupSize = 2;
  expectedGroupTasksIds = new Index[expectedGroupSize];
  expectedGroupTasksIds[0] = 1; // because 3 is already chosen.
  expectedGroupTasksIds[1] = 0; // because 2 is already chosen.

  createDefaultRootGroup();
  chosen[3] = true;
  chosen[2] = true;

  generateGroup();

  ASSERT_EQ(expectedGroupSize, resultingGroup->nElements());
  for(Index i = 0; i < expectedGroupSize; ++i) {
    ASSERT_EQ(expectedGroupTasksIds[i], resultingGroup->elementAt(i)->id);  
  }
}

TEST_F(CreateGroupTests, reusingChosenArray) {
  expectedGroupSize = 2;
  expectedGroupTasksIds = new Index[expectedGroupSize];
  expectedGroupTasksIds[0] = 1;
  expectedGroupTasksIds[1] = 0;

  createDefaultRootGroup();
  generateGroup();
  generateGroup();
  
  for(Index i = 0; i < order; ++i)
    ASSERT_TRUE(chosen[i]);

  ASSERT_EQ(expectedGroupSize, resultingGroup->nElements());
  for(Index i = 0; i < expectedGroupSize; ++i) {
    ASSERT_EQ(expectedGroupTasksIds[i], resultingGroup->elementAt(i)->id);  
  }
}

// ###############################
// Tests using the CreateGroupForLevelTests Fixture
// ###############################

TEST_F(CreateGroupForLevelTests, simpleTest) {
  avlGroups = 2;

  Index expectedGroup[avlGroups*avlGroups] = {3,2,1,0};

  generateDefaultRootNode();
  generateGroupsForLevel();

  ASSERT_EQ(avlGroups, groupVector.size());

  for(Index i = 0; i < avlGroups; ++i) {
    auto group = groupVector[i];
    
    ASSERT_EQ(avlGroups, group->nElements());
    ASSERT_EQ(i, group->id);

    for(Index j = 0; j < group->nElements(); ++j)
      ASSERT_EQ(expectedGroup[i*avlGroups + j], group->elementAt(j)->id);
  }
}

TEST_F(CreateGroupForLevelTests, notExactGroupDivision) {
  avlGroups = 3;
  TaskGroup *resultingChildGroups[avlGroups]; 

  generateDefaultRootNode();
  generateGroupsForLevel();

  ASSERT_EQ(avlGroups, groupVector.size());

  for(Index i = 0; i < avlGroups; ++i) {
    resultingChildGroups[i] = groupVector[i];
  }

  ASSERT_EQ(2, resultingChildGroups[0]->nElements());
  ASSERT_EQ(3, resultingChildGroups[0]->elementAt(0)->id);
  ASSERT_EQ(2, resultingChildGroups[0]->elementAt(1)->id);

  ASSERT_EQ(1, resultingChildGroups[1]->nElements());
  ASSERT_EQ(1, resultingChildGroups[1]->elementAt(0)->id);

  ASSERT_EQ(1, resultingChildGroups[2]->nElements());
  ASSERT_EQ(0, resultingChildGroups[2]->elementAt(0)->id);
}

TEST_F(CreateGroupForLevelTests, moreGroupsThanElements) {
  avlGroups = 5;

  const Index actualGroupCount = order/2; // Since there are less elements, they will be grouped by pairs on each level to guarantee that they will be tied together.

  generateDefaultRootNode();
  generateGroupsForLevel();

  ASSERT_EQ(actualGroupCount, groupVector.size());

  for(Index i = 0; i < actualGroupCount; ++i) {
    ASSERT_EQ(2, groupVector[i]->nElements());
  }
}

TEST_F(CreateGroupForLevelTests, zeroGroupsShouldFail) {
  ASSERT_DEATH(generateGroupsForLevel(), "");
}

TEST_F(CreateGroupForLevelTests, oneGroupShouldContainAllElements) {
  avlGroups = 1;

  generateDefaultRootNode();
  generateGroupsForLevel();

  ASSERT_EQ(avlGroups, groupVector.size());
  ASSERT_EQ(order, groupVector[0]->nElements());
}

TEST_F(CreateGroupForLevelTests, testWith5Tasks) {
  delete commMatrix;

  createSimpleCommunicatonMatrixWithOrder5();
  avlGroups = 4;

  generateDefaultRootNode();
  generateGroupsForLevel();

  ASSERT_EQ(avlGroups, groupVector.size());
}

// ###############################
// Tests using the CreateGroupForLevelTests Fixture
// ###############################

/**
 * This check tests if the exact same taskGroup tree will be created, when compared to the topology tree.
 */
TEST_F(TopLevelTests, nTaskstoNPEs) {
  createDummyTopologyWithTwoLevelSharedAnd8PE();
  const UInt nLevels = 2+1; // 2 shared and 1 for PEs
  UInt sumGroupsPerLevel[nLevels+1];
  nTasks = 8;
  createSimpleCommunicatonMatrixWithOrderN(nTasks);

  executeAlgorithm();

  ASSERT_EQ(nElementsLevel[2], resultingGroup->nElements());
  for(UInt i = 0; i < nLevels; ++i)
    sumGroupsPerLevel[i] = 0;
  // Should have the same predicted ammount of groups as topology elements.
  recursiveCountGroups(resultingGroup, nLevels, sumGroupsPerLevel);
  for(UInt i = 0; i < nLevels; ++i)
    ASSERT_EQ(nElementsLevel[i], sumGroupsPerLevel[i]) << "at index " << i;
}

/**
 * This tests checks if no additional groups will be made. Altough it doesn't check if the leaf nodes have different elements as they should.
 */
TEST_F(TopLevelTests, nPlusOneTaskstoNPEs) {
  createDummyTopologyWithTwoLevelSharedAnd8PE();
  const UInt nLevels = 2+1; // 2 shared and 1 for PEs
  UInt sumGroupsPerLevel[nLevels+1];
  nTasks = 8+1;
  createSimpleCommunicatonMatrixWithOrderN(nTasks);

  executeAlgorithm();

  ASSERT_EQ(nElementsLevel[2], resultingGroup->nElements());

  for(UInt i = 0; i < nLevels; ++i)
    sumGroupsPerLevel[i] = 0;

  // Should have the same predicted ammount of groups as topology elements.
  recursiveCountGroups(resultingGroup, nLevels, sumGroupsPerLevel);
  for(UInt i = 0; i < nLevels; ++i)
    ASSERT_EQ(nElementsLevel[i], sumGroupsPerLevel[i]) << "at index " << i;
}

/**
 * This tests checks if no additional groups will be made.
 */
TEST_F(TopLevelTests, twoNTaskstoNPEs) {
  createDummyTopologyWithTwoLevelSharedAnd8PE();
  const UInt nLevels = 2+1; // 2 shared and 1 for PEs
  UInt sumGroupsPerLevel[nLevels+1];
  nTasks = 8*2;
  createSimpleCommunicatonMatrixWithOrderN(nTasks);

  executeAlgorithm();

  ASSERT_EQ(nElementsLevel[2], resultingGroup->nElements());

  for(UInt i = 0; i < nLevels; ++i)
    sumGroupsPerLevel[i] = 0;

  // Should have the same predicted ammount of groups as topology elements.
  recursiveCountGroups(resultingGroup, nLevels, sumGroupsPerLevel);
  for(UInt i = 0; i < nLevels; ++i)
    ASSERT_EQ(nElementsLevel[i], sumGroupsPerLevel[i]) << "at index " << i;
}

/**
 * This checks if exactly one group will be created, since no more is needed than that.
 */
TEST_F(TopLevelTests, oneTaskstoNPEs) {
  createDummyTopologyWithTwoLevelSharedAnd8PE();
  const UInt nLevels = 2+1; // 2 shared and 1 for PEs
  UInt sumGroupsPerLevel[nLevels+1];
  nTasks = 1;
  createSimpleCommunicatonMatrixWithOrderN(nTasks);

  executeAlgorithm();

  for(UInt i = 0; i < nLevels; ++i)
    sumGroupsPerLevel[i] = 0;

  // Should have the same predicted ammount of groups as topology elements.
  recursiveCountGroups(resultingGroup, nLevels, sumGroupsPerLevel);
  EXPECT_EQ(1, sumGroupsPerLevel[2]) << "at index " << 2;
  EXPECT_EQ(1, sumGroupsPerLevel[1]) << "at index " << 1;
  EXPECT_EQ(1, sumGroupsPerLevel[0]) << "at index " << 0;
}

/**
 * This checks if exactly one groups will be created, since the tasks will be grouped together to one PE.
 */
TEST_F(TopLevelTests, twoTaskstoNPEs) {
  createDummyTopologyWithTwoLevelSharedAnd8PE();
  const UInt nLevels = 2+1; // 2 shared and 1 for PEs
  UInt sumGroupsPerLevel[nLevels+1];
  nTasks = 2;
  createSimpleCommunicatonMatrixWithOrderN(nTasks);

  executeAlgorithm();

  for(UInt i = 0; i < nLevels; ++i)
    sumGroupsPerLevel[i] = 0;

  // Should have the same predicted ammount of groups as topology elements.
  recursiveCountGroups(resultingGroup, nLevels, sumGroupsPerLevel);
  EXPECT_EQ(1, sumGroupsPerLevel[2]) << "at index " << 2;
  EXPECT_EQ(1, sumGroupsPerLevel[1]) << "at index " << 1;
  EXPECT_EQ(1, sumGroupsPerLevel[0]) << "at index " << 0; // One leaf node. It's a special case since it has to be grouped to properly work.
}

/**
 * This checks if exactly two groups will be created, since no more is needed than that.
 */
TEST_F(TopLevelTests, threeTaskstoNPEs) {
  createDummyTopologyWithTwoLevelSharedAnd8PE();
  const UInt nLevels = 2+1; // 2 shared and 1 for PEs
  UInt sumGroupsPerLevel[nLevels+1];
  nTasks = 3;
  createSimpleCommunicatonMatrixWithOrderN(nTasks);

  executeAlgorithm();

  for(UInt i = 0; i < nLevels; ++i)
    sumGroupsPerLevel[i] = 0;

  // Should have the same predicted ammount of groups as topology elements.
  recursiveCountGroups(resultingGroup, nLevels, sumGroupsPerLevel);
  EXPECT_EQ(1, sumGroupsPerLevel[2]) << "at index " << 2;
  EXPECT_EQ(1, sumGroupsPerLevel[1]) << "at index " << 1;
  EXPECT_EQ(2, sumGroupsPerLevel[0]) << "at index " << 0; // One leaf node. It's a special case since it has to be grouped to properly work.
}

}