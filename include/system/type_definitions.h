#pragma once

#include <system/traits.h>

namespace MOGSLib {

namespace Policy {
  using TaskEntry = Traits<Policies>::TaskEntry;
  using TaskMap = Traits<Policies>::TaskMap;

  using Index = Traits<DefaultTypes>::Index;
  using Load = Traits<DefaultTypes>::Load;
}

namespace Scheduler {
  using TaskEntry = Policy::TaskEntry;
  using TaskMap = Policy::TaskMap;

  using Index = Policy::Index;
  using Load = Policy::Load;
}

namespace Abstraction {
  using TaskEntry = Policy::TaskEntry;
  using TaskMap = Policy::TaskMap;

  using Index = Policy::Index;
  using Load = Policy::Load; 
}

namespace Adapter {
  using Index = Policy::Index;
  using Load = Policy::Load;  
}

}