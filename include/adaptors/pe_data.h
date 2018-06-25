#pragma once

namespace Concepts {

/**
 * @brief A concept that displays methods to gather the data about the platform PEs.
 */
template<typename Concrete>
class PEData {
public:
  Concrete *c;

  /**
   * @brief Get the amount of PEs in the platform.
   */
  inline decltype(c->ntasks()) nPEs() {
    return c->nPEs();
  }

  /**
   * @brief Get the workloads of the PEs in the platform.
   */
  inline decltype(c->PEs_workloads()) PEs_workloads() {
    return c->PEs_workloads();
  }

};

}