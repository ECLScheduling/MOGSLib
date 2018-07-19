#pragma once

namespace MOGSLib {

struct DefaultTypes;
class Policies;

enum SchedulerTypes {
  Null,
  RoundRobin,
  Compact,
  TaskPack,
  Greedy
};

}