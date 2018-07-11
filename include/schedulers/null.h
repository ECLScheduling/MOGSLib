#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief A scheduler that makes nothing.
 */
class Null : public Abstraction::Scheduler {
public:
  static constexpr auto TypeToken = MOGSLib::SchedulerTypes::Null;

  Null() : Scheduler(SchedulerTraits<TypeToken>::name) {}
  virtual ~Null() {}
};

END_NAMESPACE