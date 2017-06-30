#pragma once

#include <system/traits.h>
#include <set>

/**
 * The abstract class which intends to be the simplest possible input to a parallel strategy, carrying only the PEs ids and each task's load and id.
 */
template<typename TaskType = IMinimalParallelInputTraits::Task, typename PEType = IMinimalParallelInputTraits::PE>
class IMinimalParallelInput {
public:
  typedef TaskType Task;
  typedef PEType PE;

  /**
   * @return A pointer to an array of PEs.
   */
  virtual PE * getPEs() const = 0;

  /**
   * @return The ammount of PEs in this input.
   */
  virtual const unsigned int PECount() const = 0;

  /**
   * @return A pointer to an array of tasks.
   */
  virtual Task * getTasks() const = 0;

  /**
   * @return The ammount of Tasks in this input.
   */
  virtual const unsigned int taskCount() const = 0;
};

typedef IMinimalParallelInput<> IDefaultMinimalParallelInput;