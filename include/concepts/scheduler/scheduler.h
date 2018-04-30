#pragma once

#include <system/traits.h>

#include "scheduler_input.h"

namespace Concepts {

/**
 * @brief A class that declares the conceptual scheduler.
 */
template<typename Input>
class Scheduler {
public:

  using Output = Traits<SchedulerOutput>::Output;

  Scheduler(){}
  virtual ~Scheduler() {}

  virtual Output map(Input &input);
};

}