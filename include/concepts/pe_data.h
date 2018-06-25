#pragma once

namespace Concepts {

/**
 * @brief A concept that displays methods to gather the data about the platform PEs.
 */
template<typename Concrete>
struct PEData {
  static Concrete *c;

  /**
   * @brief Get the amount of PEs in the platform.
   */
  static inline decltype(c->ntasks()) nPEs() {
    return c->nPEs();
  }

  /**
   * @brief Get the workloads of the PEs in the platform.
   */
  static inline decltype(c->PEs_workloads()) PEs_workloads() {
    return c->PEs_workloads();
  }

};

template <typename Concrete>
Concrete* PEData<Concrete>::c = nullptr;

}