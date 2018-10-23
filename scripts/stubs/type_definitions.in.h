#pragma once

#include <system/traits/rts.h>
#include <system/traits/schedulers.h>

namespace MOGSLib {
  static constexpr auto TargetSystem = RuntimeSystemEnum::@RTS_ENUM_VAL@;
  using RTS = Abstraction::RTS<TargetSystem>;

  using Index = RuntimeTraits<TargetSystem>::Index;
  using Load = RuntimeTraits<TargetSystem>::Load;

  using TaskEntry = Index;
  using TaskMap = TaskEntry*;
}