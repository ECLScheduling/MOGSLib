#pragma once

#include <system/traits.h>

/**
 * @brief This namespace defines the data types used in Charm++ needed in adaptors.
 */
namespace CharmTypes {

  /**
   * @brief The data type that is used to quantify a PE and task's load.
   */
  using Load = double; 

  /**
   * @brief The data type that is used as the unsigned int type.
   */
  using UInt = Traits<DefaultTypes>::UInt;
};