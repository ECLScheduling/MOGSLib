#pragma once

#include <abstractions/scheduler.h>

namespace MOGSLib { namespace Scheduler {

/**
 * @brief A scheduler that makes nothing.
 */
class Null : public Abstraction::Scheduler<MOGSLib::Abstraction::null> {};

}}