#pragma once

#include <tuple>
#include <string>

#include <abstractions/traits/lulesh_charm.h>

namespace MOGSLib {  using Traits = LuleshCharm;  }

#include <abstractions/contexts/charm_base.h>

#include <schedulers/greedy.h>

#include "macros.h"

namespace MOGSLib {

struct API {
  using Contexts = std::tuple<Ctx(CharmBase)>;
  using Schedulers = std::tuple<Sched(Greedy, 0)>;

  static Contexts contexts;
  static Schedulers schedulers;

  template<unsigned i>
  inline static typename MOGSLib::Config::Policy<typename Traits::Id>::Schedule do_work();

  inline static auto work(const std::string &name) {
    SchedWork("greedy", 0)
    throw std::string("[MOGSLib] Invalid scheduler name.");
  }
};

}