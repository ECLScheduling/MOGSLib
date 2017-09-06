#include <gtest/gtest.h>

#include <structures/eagerMap/hardwareElement.h>

/**
 * Fixture for testing the EagerMap HardwareElement structure.
 */
class EagerMapHardwareElementTests : public ::testing::Test {
public:
  typedef EagerMap::HardwareElement HardwareElement;
  typedef HardwareElement::UInt UInt;
  typedef HardwareElement::Id Id;

  HardwareElement *element;
  HardwareElement *linked;

  UInt id, nSharers;
  HardwareElement::Type type;

  bool created, createdLinked;


  void SetUp() {
    created = 0;
    createdLinked = 0;
  }

  void createElement() {
    element = new HardwareElement(id, type, nSharers);
    created = 1;  
  }

  void initializeLinkedArray() {
    linked = new HardwareElement[nSharers];
    createdLinked = 1;
  }

  void setLinkedElements(){
    element->setLinkedElements(linked);
  }

  void TearDown() {
    if(created)
      delete element;

    if(createdLinked)
      delete []linked;
  }

};

TEST_F(EagerMapHardwareElementTests, creation) {
  id = 0;
  type = HardwareElement::SharedElement;
  nSharers = 2;

  createElement();
  initializeLinkedArray();

  for(UInt i = 0; i < nSharers; ++i) {
    linked[i].id = 1+i;
    linked[i].type = HardwareElement::Type::ProcessingElement;
    linked[i].nSharers = 0;
  }

  setLinkedElements();

  for(UInt i = 0; i < nSharers; ++i) {
    const HardwareElement sharer = element->link(i);
    ASSERT_EQ(i+1, sharer.id);
    ASSERT_EQ(HardwareElement::Type::ProcessingElement, sharer.type);
    ASSERT_EQ(0, sharer.nSharers);
  }
}

TEST_F(EagerMapHardwareElementTests, navigation) {
  id = 0;
  type = HardwareElement::SharedElement;
  nSharers = 2;

  // Creating and initializing the memory.
  createElement();
  initializeLinkedArray();

  // Setting the hardware elements with meaningful values.
  linked[0].id = 1;
  linked[0].type = HardwareElement::Type::SharedElement;
  linked[0].nSharers = 1; // One single child layer just to test the navigation.
  for(UInt i = 1; i < nSharers; ++i) {
    linked[i].id = 1+i;
    linked[i].type = HardwareElement::Type::ProcessingElement;
    linked[i].nSharers = 0; // Only the first linked element is a shared hardware element.
  }
  // linking the array of elements to the root element.
  setLinkedElements();

  // Creating the third layer of hardware elements.
  HardwareElement *thirdLevelElements = new HardwareElement();
  // Linking the third layer which is composed of 1 element to the first hardware element of the second layer.
  linked[0].setLinkedElements(thirdLevelElements);

  // Setting the thir layer of hardware elements with meaningful values.
  thirdLevelElements->id = nSharers; // unused id yet for testing purposes.
  thirdLevelElements->type = HardwareElement::Type::ProcessingElement;
  thirdLevelElements->nSharers = 0;


  // Testing the navigation
  HardwareElement current = *element; // at root.
  current = element->link(1); // Getting to the second link, which has no children.

  ASSERT_EQ(0, current.nSharers);
  
  current = element->link(0); // Getting to the first link, which has one child in the third layer.
  ASSERT_EQ(1, current.nSharers);

  current = current.link(0);
  ASSERT_EQ(0, current.nSharers);
  ASSERT_EQ(HardwareElement::Type::ProcessingElement, current.type);
}

TEST_F(EagerMapHardwareElementTests, wontAccessUnreachableIndex) {
  id = 0;
  type = HardwareElement::SharedElement;
  nSharers = 1;

  createElement();
  initializeLinkedArray();

  for(UInt i = 1; i < nSharers; ++i) {
    linked[i].id = 1+i;
    linked[i].type = HardwareElement::Type::ProcessingElement;
    linked[i].nSharers = 0;
  }

  ASSERT_DEATH(element->link(nSharers+1), "");
}