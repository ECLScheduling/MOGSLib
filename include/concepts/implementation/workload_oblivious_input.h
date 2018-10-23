#pragma once

#include <vector>
#include <system/type_definitions.h>

namespace MOGSLib { namespace Concept {

/**
 * @brief A concrete concept that access information about the amount of PEs and work units in the system.
 */
template<MOGSLib::RuntimeSystemEnum R = MOGSLib::TargetSystem>
class WorkloadObliviousInput {
public:
  using Index = MOGSLib::Index;
  
  Index tasks, PEs;

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   */
  inline Index ntasks() {
    return tasks;
  }

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index ntasks() const {
    return tasks;
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index nPEs() const {
    return PEs;
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   */
  inline Index nPEs() {
    return PEs;
  }
};

/**
 * @brief A concrete concept that access information about the amount of PEs and work units in the system.
 * @details A specialization for the charm system, which must retain information about the PEs and tasks ids.
 */
template<>
class WorkloadObliviousInput<MOGSLib::RuntimeSystemEnum::Charm> {
public:
  using Index = MOGSLib::Index;
  
  std::vector<Index> task_ids, PE_ids;

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   */
  inline Index ntasks() {
    return task_ids.size();
  }

  /**
   * @brief Gets the amount of tasks in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index ntasks() const {
    return task_ids.size();
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   * @details This method has a const specifier.
   */
  inline Index nPEs() const {
    return PE_ids.size();
  }

  /**
   * @brief Gets the amount of PEs in a scheduler input.
   */
  inline Index nPEs() {
    return PE_ids.size();
  }
};

}}