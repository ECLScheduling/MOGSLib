#pragma once

#include <tuple>
#include <string>

#include <abstractions/traits/libgomp_default.h>

namespace MOGSLib {  using Traits = LibgompDefault;  }

#include <abstractions/contexts/libgomp_multiloop.h>

#include <model/schedulers/buffered_binlpt.h>

#include "macros.h"

namespace MOGSLib {

struct API {
  using Contexts = std::tuple<Ctx(LibGOMPMultiloop)>;
  using Schedulers = std::tuple<Sched(BufferedBinLPT, 0)>;

  static Contexts contexts;
  static Schedulers schedulers;

  template<unsigned i>
  inline static typename MOGSLib::Config::Policy<typename Traits::Id>::Schedule do_work();

  inline static bool test_scheduler(const std::string &schedname, const std::string &name);

  inline static auto work(const std::string &name) {
    if(test_scheduler("buffered_binlpt", name))
			return do_work<0>();
    throw std::string("[MOGSLib] Invalid scheduler name.");
  }
};

}