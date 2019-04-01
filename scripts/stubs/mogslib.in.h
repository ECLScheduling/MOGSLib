#pragma once

#include <tuple>
#include <string>

$TRAITS$
namespace MOGSLib {  using Traits = $TRAITS_CLASS$;  }

$CONTEXTS$

$SCHEDULERS$

#include "macros.h"

namespace MOGSLib {

struct API {
  using Contexts = std::tuple<$CONTEXTS_CLASSES$>;
  using Schedulers = std::tuple<$SCHEDULER_CLASSES$>;

  static Contexts contexts;
  static Schedulers schedulers;

  template<unsigned i>
  inline static typename MOGSLib::Config::Policy<typename Traits::Id>::Schedule do_work();

  inline bool test_scheduler(const std::string &schedname, const std::string &name);

  inline static auto work(const std::string &name) {
    $SCHED_WORK_SNIPPETS$
    throw std::string("[MOGSLib] Invalid scheduler name.");
  }
};

}