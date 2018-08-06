#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Abstractions)

/**
 * @brief An enumerate of all the supported runtime systems for MOGSLib schedulers.
 */
enum RuntimeSystemEnum {
  custom,
  charm,
  openmp
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