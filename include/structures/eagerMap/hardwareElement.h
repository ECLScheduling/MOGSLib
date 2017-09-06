#pragma once

#include <system/traits.h>

namespace EagerMap {

/**
 * Class that represents the tree of hardware elements in the EagerMap strategy.
 */
class HardwareElement {
public:
  typedef EagerMapTraits::UInt UInt;
  typedef EagerMapTraits::Id Id;

  /**
   * A Type enum that identifies the hardware element as a ProcessingElement or a SharedElement.
   */
  enum Type {
    ProcessingElement,
    SharedElement
  };

  /**
   * The id of the hardware element.
   */
  Id id;

  /**
   * The type of the hardware element.
   */
  Type type;

  /**
   * The ammount of hardware elements that share this hardware resource.
   */
  UInt nSharers;

private:
  /**
   * A pointer to a list of linked hardware elements. This array is assumed to be the size of nSharers.
   */
  HardwareElement* _link;

public:

  /**
   * Creates a HardwareElement initializing all elements but the list of linked HardwareElements that can be set up by calling setLinkedElements method.
   */
  HardwareElement(const Id &anId = 0, const Type &hwType = ProcessingElement, const UInt &qtdSharers = 0) : id(anId), type(hwType), nSharers(qtdSharers) {}

  /**
   * This class' destructor clean doesn't clean the link variables since they are passed as reference.
   */ 
  virtual ~HardwareElement() {}

  /**
   * This method is used to set the list of linked HardwareElements, this method ideally should be called only once.
   * @param elements  The list of linked HardwareElements that are linked to this HardwareElement.
   */
  void setLinkedElements(HardwareElement *elements) {
    _link = elements;
  }

  /**
   * This method is used to access the hardware links that are connected to the instance of the HardwareElement.
   * @param index The index of the link that will be retrieved, this parameter must not exceed the nSharers variable.
   */
  HardwareElement& link(const UInt &index) {
    assert(index < nSharers);
    return _link[index];
  }

};

}