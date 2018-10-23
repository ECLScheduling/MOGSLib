#pragma once

#include <memory>
#include <system/traits/schedulers.h>

namespace MOGSLib { namespace Abstraction {

/**
 * @brief A scheduler abstraction that unifies all template specializations together.
 */
template<SchedulerEnum T, typename ... _Concepts>
class Scheduler {
public:
  using Index = MOGSLib::Index;
  using Load = MOGSLib::Load;
  using TaskMap = MOGSLib::TaskMap;

protected:
  using DependencyStructure = typename MOGSLib::SchedulerTraits<T>::template Dependencies<_Concepts...>;
  std::shared_ptr<DependencyStructure> concepts;

public:
  /**
   * @brief The method that will initialize the references to the concrete concepts used by the scheduler.
   */
  void init(std::tuple<_Concepts *...> ref) {
    concepts = std::make_shared<DependencyStructure>(ref);
  }

  /**
   * @brief Get the enum value in SchedulerEnum associated with this scheduler.
   */
  static constexpr SchedulerEnum scheduler_type() {
    return T;
  }

  /**
   * @brief The method to obtain a task map based on a compact policy.
   **/
  virtual TaskMap work() {
    return nullptr;
  }

  virtual ~Scheduler() {}
};

}}
