#pragma once

#include <gtest/gtest.h>
#include <system/traits.h>
#include <iostream>

#include <algorithms/eagerMap/eagerMapAlgorithm.h>

namespace EagerMapCommunicationTests {

// Define this variable to true to print data about the algorithm.
#define DEBUG_ENABLED false

/**
 * This class is a helper class that creates the matrix of communication for all the tests in the SetUp.
 */
class AlgorithmTest : public ::testing::Test, public EagerMap::Algorithm {
public:
  typedef EagerMap::Algorithm Algorithm;

  typedef Algorithm::CommunicationMatrix CommunicationMatrix;
  typedef Algorithm::Index Index;
  typedef Algorithm::Communication Communication;

  typedef Algorithm::TaskGroupVector TaskGroupVector;
  typedef Algorithm::TaskGroup TaskGroup;

  CommunicationMatrix *commMatrix;
  Index order;
  TaskGroupVector groupVector;

  void createSimpleCommunicatonMatrixWithOrderN(const Index anOrder) {
    order = anOrder;

    commMatrix = new CommunicationMatrix(order, 0);

    Index w = 1;
    for(Index i = 0; i < order; ++i) {
      for(Index j = i+1; j < order; ++j) {
        commMatrix->at(i,j) = w;
        commMatrix->at(j,i) = w;
        ++w;
      }
    }
  }

  /**
   * Creates a simple communication matrix to be used on the tests.
   */
  void createSimpleCommunicatonMatrixWithOrder4() {

    /** Communication Matrix
     * | 0 1 2 3 |
     * | 1 0 4 5 |
     * | 2 4 0 6 |
     * | 3 5 6 0 |
     */
    createSimpleCommunicatonMatrixWithOrderN(4);
  }

  void createSimpleCommunicatonMatrixWithOrder5() {

    /** Communication Matrix
     * | 0 1 2 3 4 |
     * | 1 0 4 5 6 |
     * | 2 4 0 6 7 |
     * | 3 5 6 0 7 |
     * | 4 5 6 7 0 |
     */
    createSimpleCommunicatonMatrixWithOrderN(5);
  }

  void SetUp() {
    groupVector.clear();
    createSimpleCommunicatonMatrixWithOrder4();
  }

  void TearDown() {
    delete commMatrix;
    for(TaskGroup *g : groupVector) {
      delete g;
    }
  }

};

/**
 * This class is a helper class that creates the groups to test the recreation of the matrix topology.
 */
class CreateCommunicationMatrixTest : public AlgorithmTest {
public:

  /**
   * A proxy method to the tested class-method. This method is here since it is called in every test in this suite.
   */
  void recreateCommunicationMatrix() {
    Algorithm::recreateCommunicationMatrix(commMatrix, groupVector);
  }


  /**
   * Creates a regular group in the rootGroup varible. The groups is as below:
   *           0
   *          / \
   *         /   \
   *        0     1
   *       / \   / \
   *      0   1 2   3
   *
   * Tasks: 0,1,2,3
   */
  void createRegularGroupOn3LevelsWith4Tasks() {
    TaskGroup *left, *right;

    left = new TaskGroup(0);
    right = new TaskGroup(1);

    left->setElement(new TaskGroup(0));
    left->setElement(new TaskGroup(1));

    right->setElement(new TaskGroup(2));
    right->setElement(new TaskGroup(3));

    groupVector.push_back(left);
    groupVector.push_back(right);
  }

  /**
   * Creates an irregular group in the rootGroup varible. The groups is as below:
   *           0
   *         / | \
   *        /  |  \
   *       0   1   2
   *      / \   \   \
   *     0   1   2   3
   *
   * Tasks: 0,1,2,3
   */
  void createIrregularGroupOn3LevelsWith4Tasks() {
    TaskGroup *left, *right, *middle;

    left = new TaskGroup(0);
    middle = new TaskGroup(1);
    right = new TaskGroup(2);

    left->setElement(new TaskGroup(0));
    left->setElement(new TaskGroup(1));

    middle->setElement(new TaskGroup(2));

    right->setElement(new TaskGroup(3));

    groupVector.push_back(left);
    groupVector.push_back(middle);
    groupVector.push_back(right);

  }

  void SetUp() {
    AlgorithmTest::SetUp();
  }

  void TearDown() {
    AlgorithmTest::TearDown();
  }

};

/**
 * This class is a fixture for the algorithm that creates the groups of elements.
 */
class CreateGroupTests : public AlgorithmTest {
public:

  TaskGroup *resultingGroup;

  Index expectedGroupSize;
  Index *expectedGroupTasksIds;

  bool *chosen;

  /**
   * Creates the default group setup for these group creation tests, which looks like this:
   *
   * Group Tree:
   *     0
   *  0 1 2 3 
   *
   * Tasks: 0,1,2,3
   */
  void createDefaultRootGroup() {
    for(Index i = 0; i < order; ++i)
      groupVector.push_back(new TaskGroup(i));  
  }

  /**
   * Creates an invalid group structure with out-of order ids, which looks like this:
   *
   * Group Tree:
   *     0
   *  3 2 1 0 
   *
   * Tasks: 0,1,2,3
   */
  void createUnorderedRootGroup() {
    for(Index i = 0; i < order; ++i)
      groupVector.push_back(new TaskGroup(3-i));
  }

  /**
   * Allocate and initializes the chosen array with all the values set as false.
   */
  void initializechosenArrayWithFalse() {
    chosen = new bool[order];
    for(Index i = 0; i < order; ++i)
      chosen[i] = false;
  }

  /**
   * This method calls the proxy method with the 'chosen' parameter initialized as every element in false.
   */
  void generateGroup() {
    resultingGroup = new TaskGroup();
    Algorithm::generateGroup(commMatrix, groupVector, expectedGroupSize, chosen, *resultingGroup);
  }

  void SetUp() {
    AlgorithmTest::SetUp();
    initializechosenArrayWithFalse();
  }

  void TearDown() {
    delete commMatrix;
    fullCleanup();
  }

  void fullCleanup() {
    delete [] expectedGroupTasksIds;
    delete [] chosen;
    delete resultingGroup;
  }
};

/**
 * This class is a fixture for the algorithm that creates all the groups in a given level.
 */
class CreateGroupForLevelTests : public AlgorithmTest {
public:

  Index avlGroups;

  /**
   * Generate a group of child nodes and the root nodes with the default communication matrix.
   */
  void generateDefaultRootNode() {
    for(Index i = 0; i < order; ++i)
      groupVector.push_back(new TaskGroup(i));
  }

  /**
   * Proxy method to the tested feature of this fixture.
   */
  void generateGroupsForLevel() {
    Algorithm::generateGroupsForLevel(commMatrix, groupVector, avlGroups);
  }

  void SetUp() {
    AlgorithmTest::SetUp();
  }

  void TearDown() {
    AlgorithmTest::TearDown();
  }

};

class TopLevelTests : public AlgorithmTest {
public: 

  typedef EagerMap::TopologyData TopologyData;
  typedef EagerMap::HardwareElement HardwareElement;
  typedef Algorithm::UInt UInt;

  TopologyData *topologyData;
  UInt nTasks;


  TaskGroup *resultingGroup;
  UInt nSharedLevels, *nElementsLevel;
  HardwareElement **hwLevelNodes, *hwRootNode;

  /**
   * Proxy method to the tested top level algorithm
   */
  void executeAlgorithm() {
    resultingGroup = Algorithm::mapAlgorithm(commMatrix, *topologyData);

    if(DEBUG_ENABLED) {
      printTaskGroup(resultingGroup, 0);
    }
  }

  void printTaskGroup(TaskGroup *node, const UInt level) {
    for(UInt i = 0; i < level; ++i)
      std::cout << "  ";
    std::cout << node->id << std::endl;
    for(UInt i = 0; i < node->nElements(); ++i)
      printTaskGroup(node->elementAt(i), level+1);
  }

  /**
   * Creates the needed input to the tested method.
   */
  void createTopologyData() {
    topologyData = new TopologyData(nSharedLevels, nElementsLevel, hwRootNode);
  }

  /**
   * Allocate the array of ammount of elements in the hardware topology.
   * @param sharedLevels The quantity of shared levels.
   */
  void allocateElementsLevelArray(const UInt &sharedLevels) {
    nSharedLevels = sharedLevels;
    nElementsLevel = new UInt[nSharedLevels+1];
  }

  /**
   * Creates a dummy binary tree topology with 2 layers of shared interconnections merged by the root node.
   */
  void createDummyTopologyWithTwoLevelSharedAnd8PE() {
    const UInt sharedLevels = 2;
    const UInt totalLevels = sharedLevels+1;

    allocateElementsLevelArray(sharedLevels);

    /**
     * [2] Third shared level  ->  2 interconnections
     * [1] Second shared level ->  4 interconnections
     * [0] PEs                 ->  8 instances
     */
    nElementsLevel[0] = 8;

    
    // Creating a Binary Tree to represent the topology.
    hwLevelNodes = new HardwareElement*[totalLevels];
    for(UInt i = 1; i < totalLevels; ++i)
      nElementsLevel[i] = nElementsLevel[i-1]/2;  
    for(UInt i = 0; i < totalLevels; ++i)
      hwLevelNodes[i] = new HardwareElement[nElementsLevel[i]];
    
    // All the processors are associated with a correct id.
    for(UInt i = 0; i < nElementsLevel[0]; ++i)
      hwLevelNodes[0][i].id = i;

    for(UInt i = 1; i < totalLevels; ++i){
      auto elementsThisLevel = nElementsLevel[i];
      auto elementsPastLevel = nElementsLevel[i-1];

      for(UInt j = 0; j < elementsThisLevel; ++j){
        HardwareElement &hwRef = hwLevelNodes[i][j];
        hwRef.id = j;
        hwRef.type = HardwareElement::SharedElement;
        hwRef.nSharers = elementsPastLevel/elementsThisLevel;
        hwRef.setLinkedElements(&(hwLevelNodes[i-1][j*hwRef.nSharers]));
      }
    }
    
    hwRootNode = new HardwareElement(0, HardwareElement::SharedElement, nElementsLevel[sharedLevels]);
    hwRootNode->setLinkedElements(hwLevelNodes[nSharedLevels]);
    createTopologyData();
  }

  void recursiveCountGroups(TaskGroup *curNode, const UInt &level, UInt *sum) {
    auto childCount = curNode->nElements();
  
    for(UInt i = 0; i < childCount; ++i)
      recursiveCountGroups(curNode->elementAt(i), level-1, sum);
    sum[level] += 1;
  }

  void SetUp() {
  }

  void TearDown() {
    delete commMatrix;
    fullCleanup();
  }

  void fullCleanup() {
    delete topologyData;
    delete resultingGroup;
  }
};

}