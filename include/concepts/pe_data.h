#pragma once

namespace Concepts {

/**
 * @brief A concept that displays methods to gather the data about the platform PEs.
 */
template<typename Concrete>
struct PEData {
  static Concrete *concrete;

  /**
   * @brief Get the amount of PEs in the platform.
   */
  static inline decltype(concrete->ntasks()) nPEs() {
    return concrete->nPEs();
  }

  /**
   * @brief Get the workloads of the PEs in the platform.
   */
  static inline decltype(concrete->PEs_workloads()) PEs_workloads() {
    return concrete->PEs_workloads();
  }

};

template <typename Concrete>
Concrete* PEData<Concrete>::concrete = nullptr;

}