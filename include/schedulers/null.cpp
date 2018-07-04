#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief A scheduler that makes nothing.
 */
class Null : public Abstraction::Scheduler {
public:

  NoScheduler() : Scheduler("nosched") {}
  virtual ~NoScheduler() {}
};

END_NAMESPACE