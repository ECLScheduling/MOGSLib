#pragma once

#include "openmpAdaptorDefault.h"
#ifdef RTS_IS_OPENMP

#include <interfaces/adaptor/extensions/withGenericStructure.h>

/**
 * @brief This class is an extended adaptor for OpenMP++ that serves the purpose of implementing the WithGenericStructure interface.
 * @details This class uses the same initialization code that the OpenMPDefaultAdaptor.
 */
template<typename T>
class OpenMPAdaptorWithGenericStructure : public OpenMPDefaultAdaptor, public WithGenericStructure<T> {
protected:

  /**
   * @variable ref A reference to the structure that this input adaptor encapsulates.
   */
  T ref;

public:

  OpenMPAdaptorWithGenericStructure() : OpenMPDefaultAdaptor(){}

  /**
   * Initializes the reference to the structure that this adaptor provides to the strategy.
   * @param structure_ref The reference to the structure.
   */
  void setStructure(T &structure_ref) {
    ref = structure_ref;
  }

  /**
   * A method to obtain the additional input structure.
   */
  inline T &structure() {
    return ref;
  }
};

#endif