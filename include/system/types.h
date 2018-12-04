#pragma once

namespace MOGSLib {

/// @brief An enumeration of all MOGSLib supported runtime systems.
enum RuntimeSystemEnum {
  NoRTS,
  Custom,
  Charm,
  OpenMP
};

/// @brief An enumeration of all MOGSLib implemented global schedulers.
enum SchedulerEnum {
  round_robin,
  compact,
  task_pack,
  greedy,
  binlpt
};

/// @brief An enumeration of all input types possible in MOGSLib implemented global schedulers.
enum InputEnum {
  simple,
  workload_aware
};

}