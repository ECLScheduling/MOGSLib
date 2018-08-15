#pragma once

#include <abstractions/scheduler.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief A scheduler that makes nothing.
 */
class Null : public Abstraction::Scheduler<MOGSLib::Abstraction::null> {};

END_NAMESPACE