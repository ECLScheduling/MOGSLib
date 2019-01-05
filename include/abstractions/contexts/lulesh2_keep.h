#pragma once

#include <abstractions/contexts/lulesh2_ctx.h>
#include <mogslib/config.h>

namespace MOGSLib { namespace Context {

struct Lulesh2Keep : public Lulesh2 {
  MOGSLib::Config::Policy<typename Traits::Id>::Schedule _schedule = nullptr;

  inline bool has_schedule() { return _schedule != nullptr; }

  inline auto schedule() { return _schedule; }

  inline void set_schedule(decltype(_schedule) sched) { _schedule = sched; }
};

}}