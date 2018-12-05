#pragma once

#include <type_definitions.h>
#include <memory>

namespace UnitTest {

using Index = MOGSLib::Index;
using Load = MOGSLib::Load;
using TaskMap = MOGSLib::TaskMap;
using TaskEntry = MOGSLib::TaskEntry;

struct TaskMapUtils {
  std::unique_ptr<TaskMap> map;

  void alloc(const Index &n) {  map = std::make_unique(new TaskEntry[n]());  }

  void clear() {  map.reset(nullptr);  }

  auto get() {  return *map;  }

  auto operator[](const Index &n) {  return (*map)[n];  }
};

}