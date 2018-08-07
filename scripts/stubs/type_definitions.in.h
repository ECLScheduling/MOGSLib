#pragma once

#include <system/traits/rts.h>
#include <system/traits/schedulers.h>

namespace MOGSLib {
  static constexpr auto TargetSystem = MOGSLib::Abstraction::RuntimeSystemEnum::@RTS_ENUM_VAL@;

  using Index = RuntimeTraits<TargetSystem>::Index;
  using Load = RuntimeTraits<TargetSystem>::Load;

  using TaskEntry = Index;
  using TaskMap = TaskEntry*;
}