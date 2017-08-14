#pragma once

#include <system/traits.h>

#include <vector>

#include <structures/eagerMap/communicationMatrix.h>
#include <structures/eagerMap/taskGroup.h>
#include <structures/eagerMap/topologyData.h>

#include <iostream>

namespace EagerMap {

/**
 * This class is compound by all the algorithms that forms the EagerMap Strategy.
 */
class Algorithm {
public:

  typedef EagerMapTraits::CommunicationMatrix CommunicationMatrix;
  typedef CommunicationMatrix::IndexType Index;
  typedef CommunicationMatrix::ValueType Communication;

  typedef EagerMapTraits::TaskGroup TaskGroup;
  typedef std::vector<TaskGroup*> TaskGroupVector;

  typedef EagerMapTraits::UInt UInt;

protected:
  /**
   * This algorithm coarsens the communication matrix based on the actual grouping of tasks.
   * @details This is useful since the tasks are grouped together and the individual task communication pattern turns less relevant and the group communication patterns become useful.
   * @param commMatrix A reference pointer to the current communication Matrix. After the algorithm call, this parameter will hold the new communication matrix.
   * @param groups A vector of TasksGroup objects that represent each element.
   * @return This method returns on the parameter commMatrix the new communication matrix.
   */
  static void recreateCommunicationMatrix(CommunicationMatrix * &commMatrix, TaskGroupVector groups) {
    const Index nElements = groups.size();
    const Index oldOrder = commMatrix->order;

    // Wont try to recreate a matrix if it hasn't changed it's order since no elements got coarsened together.
    if(nElements == oldOrder)
      return;

    // A new matrix is allocated since working with the same memory address would require a buffer with the same size as the matrix due to overwrites.
    CommunicationMatrix *matrix = new CommunicationMatrix(nElements, 0);

    for(Index i = 0; i < nElements-1; ++i) {
      TaskGroup *iGroup = groups[i];
      for(Index j = i+1; j < nElements; ++j) {
        TaskGroup *jGroup = groups[j];

        Communication w = 0;
        for(Index k = 0; k < iGroup->nElements(); ++k)
          for(Index z = 0; z < jGroup->nElements(); ++z)
            w += commMatrix->at(iGroup->elementAt(k)->id, jGroup->elementAt(z)->id, oldOrder);;
        matrix->at(i, j) = w;
        matrix->at(j, i) = w;
      }
    }

    delete commMatrix;
    commMatrix = matrix;
  }

  /**
   * This algorithm groups elements into a TaskGroup object. The grouping is made evaluating the TaskGroup's communication patterns, choosing greedly and iteratively the element with the most communication.
   * @details This algorithm differs from the original from the 2015 article "An Efficient Algorithm for Communication-Based Task Mapping" in the choosing of the first element in a group. While the original algorithm picks the first element, this one picks the one with the greater communication value sum amongst tasks.
   * @param commMatrix The current and relevant communication matrix between the elements.
   * @param finalGroupSize The ammount of elements that will be grouped.
   * @param groupVector A reference to the elements contained in the rootGroup.
   * @param group A reference to a already allocated memory to contain the TaskGroup object.
   */
  static void generateGroup(const CommunicationMatrix * const commMatrix, TaskGroupVector &groupVector, const Index &finalGroupSize, bool *chosen, TaskGroup &group) {
    const Index nElements = groupVector.size();
    std::vector<Index> winners;
    Index winner;

    assert(nElements >= finalGroupSize); // There must be enough items to add on each iteration.
    assert(finalGroupSize > 0); // There must be at least 1 element in a group.

    // The iteration 0 of the for loop after this block would always select the first, extracting this block is more efficient
    //###########################################
    Index seed;
    seed = commMatrix->filteredMaxRowSum(chosen);
    chosen[seed] = true;
    winners.push_back(seed);
    group.setElement(groupVector[seed]);
    //###########################################
    // Starting at i=1 is better since it avoid nElements internal loop executions.
    // Each iteration of this loop adds an element to the newly created group.
    for(Index i = 1; i < finalGroupSize; ++i) {
      Communication wMax = 0;
      bool selectedAWinner = false;

      // Each iteration of this loop calculates the index 'winner' of the element with the most communication with the current group elements.
      for(Index j = 0; j < nElements; ++j) {
        if(chosen[j] == true)
          continue;

        // Iteratively selects an index where the element has the greatest ammount of communication with the elements that forms the group in construction.
        // This can be parallelized.
        Communication w = 0;
        for(Index k = 0; k < i; ++k) {
          w += commMatrix->at(j, groupVector[winners[k]]->id);
          if(w >= wMax) {
            wMax = w;
            winner = j;
            selectedAWinner = true;
          }
        }
      }
      
      // This assertion is to guarantee that each round of the for loop will pick a new element.
      // This case will only happen if the ammount of 'false' values inside the chosen array is lesser than the parameter finalGroupSize, since a winner will not be set in the for-loop iteration.
      assert(selectedAWinner);

      chosen[winner] = true;
      winners.push_back(winner);
      group.setElement(groupVector[winner]);
    }
  }

  /**
   * This method creates all the groups for a given level of the hierarchy.
   * @details Creates a sufficient ammount of groups through the grouping of the child elements of the parameter groupVector. The return of this method is made by the override of the rootGroup parameter.
   * @details If there are less elements than nodes in the topology, group the tasks together by pairs on each level. Altought that would generate an unbalance, since there are a low ammount of tasks and it's a rare case, the impacts should be minimal.
   * @param commMatrix The communication matrix that will be needed to create each unique group.
   * @param groupVector A reference to a vector of groups that will be updated in this method.
   * @param nGroups The expected ammount of groups to be made.
   */
  static void generateGroupsForLevel(const CommunicationMatrix * const commMatrix, TaskGroupVector &groupVector, UInt nGroups) {
    const Index nElements = groupVector.size();
    UInt grouped;
    Index elPerGroup, leftover;
    Index groupId;
    bool chosen[nElements];
    TaskGroupVector newGroupVector;

    // There must be at least one element to group.
    assert(nElements > 0);

    // Calculate the ammount of groups.
    nGroups = (nElements < nGroups)? (nElements+1)/2 : nGroups;
    // Calculate the ammount of elements per groups.
    elPerGroup = nElements / nGroups;
    // Calculate the ammount of elements that got left over and need to be merged to a group.
    leftover = nElements%nGroups;
    //leftover = nElements - elPerGroup*nGroups;

    // Initialize the chosen array.
    for(Index i = 0; i < nElements; ++i)
      chosen[i] = false;
    
    groupId = 0;
    // Each iteration creates a new group, marks off the chosen ones,
    for(UInt i = 0; i < nElements; i += grouped) {
      // Set control variables
      Index inGroup = elPerGroup;
      if(leftover > 0) {
        ++inGroup;
        --leftover;
      }

      // Create a new group class inside the previously allocated memory space
      TaskGroup *newGroup = new TaskGroup();
      generateGroup(commMatrix, groupVector, inGroup, chosen, *newGroup);
      newGroup->id = groupId;
      newGroupVector.push_back(newGroup);

      ++groupId;
      grouped = inGroup;
    }

    groupVector = newGroupVector;
  }

public:

  /**
   * This method creates the TaskGroup tree that will represent how the algorithm grouped the tasks in the different levels of the topology.
   * @details The ammount of tasks is assumed to be the same as the order of the communication matrix. The matrix has to be trimmed if there are non-migrateable tasks as this algorithm will attemp to migrate them.
   * @param communicationMatrix A communication matrix pointer to reference. This variable WILL be changed during the execution of the algorithm and ultimately will represent the communication of the topmost layer of the tree.
   * @param topologyData A reference to a TopologyData object needed for the information about each level in the topology hierarchy.
   * @return A TaskGroup which serves as a root element to the grouped task hierarchy. Each nested TaskGroup is allocated inside this class and must be cleared from memory after use by the objects that use it after this method call.
   */
  static TaskGroup* mapAlgorithm(CommunicationMatrix * &communicationMatrix, const TopologyData &topologyData) {
    const UInt nTasks = communicationMatrix->order;

    // Creates a vector of groups to use inside the algorithm.
    TaskGroupVector groupVector;
    UInt nLevels= topologyData.nLevels;

    // The first root group will only contain the tasks.
    for(UInt i = 0; i < nTasks; ++i){
      TaskGroup *task = new TaskGroup(i);
      groupVector.push_back(task);
    }

    // For each topology hierarchy level, group the current 'element groups' into more coarsened groups.
    for(UInt i = 0; i < nLevels; ++i) {
      generateGroupsForLevel(communicationMatrix, groupVector, topologyData.elementsInLevel[i]);

      // In each step the communication matrix must be coarsened aswell. This is futile in the last iteration and avoided as an optimization.
      if(i < nLevels-1)
        recreateCommunicationMatrix(communicationMatrix, groupVector);
    }

    TaskGroup *rootNode = new TaskGroup(0);
    for(auto node : groupVector)
      rootNode->setElement(node);
    return rootNode;
  }

};


}