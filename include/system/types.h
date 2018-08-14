#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief An enumerate of all the supported runtime systems for MOGSLib schedulers.
 */
enum RuntimeSystemEnum {
  Testing,
  Custom,
  Charm,
  OpenMP
};

/**
 * @brief An enumerate of all the schedulers that MOGSLib can expose.
 */
enum SchedulerEnum {
  null,
  round_robin,
  compact,
  task_pack,
  greedy
};

END_NAMESPACE