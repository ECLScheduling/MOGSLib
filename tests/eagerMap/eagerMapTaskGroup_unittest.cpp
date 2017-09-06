#include <gtest/gtest.h>

#include <structures/eagerMap/taskGroup.h>

using namespace EagerMap;

class EagerMapTaskGroup : public ::testing::Test {
public:

  typedef TaskGroup::Id Id; 
  typedef TaskGroup::UInt UInt;

  TaskGroup *group, *elements;
  UInt id;

  bool created, elementsCreated;

  void SetUp() {
    created = false;
    elementsCreated = false;
  }

  void createGroup() {
    group = new TaskGroup(id);
    created = true;
  }

  void createElements(const UInt &size) {
    elements = new TaskGroup[size];
    elementsCreated = true;
  }

  void TearDown() {
    if(created)
      delete group;
    if(elementsCreated)
      delete [] elements;
  }

};

TEST_F(EagerMapTaskGroup, creation) {  
  UInt nTasks = 2;

  id = 0;

  createGroup();
  createElements(nTasks);

  for(UInt i = 0; i < nTasks; ++i) {
    elements[i].id = i+1;
  }

  group->setElements(elements, nTasks);

  ASSERT_EQ(id, group->id);
  for(UInt i = 0; i < nTasks; ++i) {
    ASSERT_EQ(i+1, group->elementAt(i)->id);
  }
}

TEST_F(EagerMapTaskGroup, navigation) {  
  /* An example of irregular group configuration.
  *        0
  *       / \
  *      1   2
  *     /|\  
  *    3 4 5
  */
  UInt nTasksgroups = 2;
  UInt nLeavesTasks = 3;

  TaskGroup *leaves;

  id = 0;

  createGroup();
  createElements(nTasksgroups);

  // Setting the second level of the hierarchy to the root node.
  for(UInt i = 0; i < nTasksgroups; ++i) {
    elements[i].id = i+1;
  }

  group->setElements(elements, nTasksgroups);
  //############################################################

  // Setting the third and last layer of the hierarchy to the second-level's first element.
  leaves = new TaskGroup[nLeavesTasks];
  for(UInt i = 0; i < nLeavesTasks; ++i) {
    leaves[i].id = i+1 + elements[nTasksgroups-1].id;
  }

  elements[0].setElements(leaves, nLeavesTasks);
  //############################################################

  TaskGroup *current = group;

  ASSERT_EQ(id, current->id);
  for(UInt i = 0; i < nTasksgroups; ++i) {
    current = group->elementAt(i);
    ASSERT_EQ(i+1, current->id);
  }

  current = group->elementAt(0);
  for(UInt i = 0; i < nLeavesTasks; ++i) {
    ASSERT_EQ(i+1 + elements[nTasksgroups-1].id, current->elementAt(i)->id); 
  }

  delete [] leaves;
}

TEST_F(EagerMapTaskGroup, cannotAccessOutOfIndexElements) {
  UInt nTasks = 2;
  id = 0;

  createGroup();
  createElements(nTasks);

  for(UInt i = 0; i < nTasks; ++i) {
    elements[i].id = i+1;
  }
  group->setElements(elements, nTasks);


  ASSERT_DEATH(group->elementAt(nTasks), "");
}