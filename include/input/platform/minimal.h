#pragma once

#include <system/traits.h>

namespace Input {

struct MinimalPlatformData {
  using Load = typename Traits<SchedulerInput>::Load;
  using Index = typename Traits<SchedulerInput>::Index;

  Index nPEs;
  Load *PE_loads;
};

}