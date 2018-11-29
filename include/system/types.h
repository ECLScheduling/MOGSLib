#pragma once

namespace MOGSLib {

/**
 * @brief An enumerate of all the supported runtime systems types that MOGSLib exposes.
 */
enum RuntimeSystemEnum {
  NoRTS,
  Custom,
  Charm,
  OpenMP
};

/**
 * @brief An enumerate of all the schedulers types that MOGSLib can exposes.
 */
enum SchedulerEnum {
  round_robin,
  compact,
  task_pack,
  greedy,
  binlpt
};

/**
 * @brief An enumerate of all the scheduler inputs types that MOGSLib exposes.
 */
enum InputEnum {
  simple,
  workload_aware
};

}