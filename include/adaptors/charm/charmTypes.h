#pragma once

#include <system/traits.h>

/**
 * This namespace defines the data types used in Charm++ needed in adaptors.
 */
namespace CharmTypes {

  /**
   * The data type that is used to quantify a PE and task's load.
   */
  using Load = double; 

  using UInt = Traits<void>::UInt;
};