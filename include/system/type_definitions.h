#pragma once

#include <mogslib/mogslib.h>

namespace MOGSLib {
  using Index = RuntimeTraits<MOGSLib::Definitions::system>::Index;
  using Load = RuntimeTraits<MOGSLib::Definitions::system>::Load;

  using TaskEntry = Index;
  using TaskMap = TaskEntry*;
}