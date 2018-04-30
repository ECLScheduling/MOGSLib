#pragma once

#include <system/traits.h>

namespace Input {

struct MinimalApplicationData {
  using Load = typename Traits<SchedulerInput>::Load;
  using Index = typename Traits<SchedulerInput>::Index;

  Index ntasks;
  Load *task_loads;
};

}