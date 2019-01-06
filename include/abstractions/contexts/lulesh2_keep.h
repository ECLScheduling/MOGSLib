#pragma once

#include <abstractions/contexts/lulesh2_ctx.h>
#include <mogslib/config.h>
#include <cstring>

namespace MOGSLib { namespace Context {

struct Lulesh2Keep : public Lulesh2 {
  using Id = typename Traits::Id;
  
  MOGSLib::Config::Policy<Id>::Schedule _schedule = nullptr;
  Id size;

  inline bool has_schedule() { return _schedule != nullptr; }

  inline auto schedule() {
    auto cpy = new Id[size];
    std::memcpy(cpy, _schedule, sizeof(Id) * size);
    return cpy;
  }

  inline void set_schedule(decltype(_schedule) sched, const Id &n) { size = n; _schedule = sched; }
};

}}