#pragma once

#include <tuple>
#include <string>

#include <abstractions/traits/lulesh2.h>

namespace MOGSLib {  using Traits = Lulesh2;  }

#include <abstractions/contexts/lulesh2_ctx.h>
#include <abstractions/contexts/lulesh2_keep.h>

#include <schedulers/binlpt.h>
#include <schedulers/keep.h>

#include "macros.h"

namespace MOGSLib {

struct API {
  using Contexts = std::tuple<Ctx(Lulesh2), Ctx(Lulesh2Keep)>;
  using Schedulers = std::tuple<Sched(BinLPT, 0), Sched(Keep, 1)>;

  static Contexts contexts;
  static Schedulers schedulers;

  template<unsigned i>
  inline static typename MOGSLib::Config::Policy<typename Traits::Id>::Schedule do_work();

  inline static auto work(const std::string &name) {
    SchedWork("binlpt", 0)
		SchedWork("keep", 1)
    throw std::string("[MOGSLib] Invalid scheduler name.");
  }
};

}