#pragma once

#include <abstractions/contexts/lulesh2_ctx.h>
#include <mogslib/config.h>

namespace MOGSLib { namespace Context {

struct Lulesh2Keep : public Lulesh2 {
  using Id = typename Lulesh2::Id;
  using Load = typename Lulesh2::Load;
  
  static MOGSLib::Config::Policy<Id>::Schedule _schedule;
  static Id size;

  static inline void set_iterations(const Id &n) { Lulesh2::set_iterations(n); }

  static inline auto& input() { return Lulesh2::input(); }

  static inline auto k() { return Lulesh2::k();  }

  static inline void set_domain(Domain *domain) { Lulesh2::set_domain(domain); }

  static inline bool has_schedule() { return _schedule != nullptr; }

  static inline auto schedule() { return _schedule; }

  static inline void set_schedule(decltype(_schedule) sched) { _schedule = sched; }
};

decltype(Lulesh2Keep::_schedule) Lulesh2Keep::_schedule = nullptr;
decltype(Lulesh2Keep::size) Lulesh2Keep::size = 0;

}}