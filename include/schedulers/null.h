#pragma once

#include <abstractions/scheduler.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief A scheduler that makes nothing.
 */
class Null : public Abstraction::Scheduler {
public:
  Null() : Scheduler(SchedulerTraits<MOGSLib::Abstraction::null>::name) {}
  virtual ~Null() {}
};

END_NAMESPACE