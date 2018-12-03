#pragma once

#include <abstractions/scheduler.h>

namespace MOGSLib { namespace Scheduler {

/**
 * \brief TODO: This scheduler needs a description.
 **/
template<typename ... _Concepts>
class $CNAME$ : public Abstraction::Scheduler<MOGSLib::SchedulerEnum::$TNAME$, _Concepts...> {
public:
  using Base = Abstraction::Scheduler<MOGSLib::SchedulerEnum::$TNAME$, _Concepts...>;

  /**
   * \brief The method to obtain a task map based on this scheduler policy.
   * @details TODO: Add a detailed description to this method based on this scheduler
   **/
  TaskMap work() override {
    auto concepts = Base::concepts;
    // TODO: write the scheduler's code or (even better) evoke a policy.
    return nullptr;
  }

};

}}