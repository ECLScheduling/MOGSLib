#pragma once

#include <tuple>
#include <string>

#include <abstractions/traits/omp_delay_test.h>

namespace MOGSLib {  using Traits = OmpDelayTest;  }

#include <abstractions/contexts/omp_delay_tests.h>

#include <schedulers/binlpt.h>

#include "macros.h"

namespace MOGSLib {

struct API {
  using Contexts = std::tuple<Ctx(OmpDelayTest)>;
  using Schedulers = std::tuple<Sched(BinLPT, 0)>;

  static Contexts contexts;
  static Schedulers schedulers;

  template<unsigned i>
  inline static typename MOGSLib::Config::Policy<typename Traits::Id>::Schedule do_work() {
    return std::get<i>(schedulers).work(std::get<i>(contexts));
  }

  inline static bool test_scheduler(const std::string &schedname, const std::string &name) {
    return !name.compare(schedname);
  }

  inline static auto work(const std::string &name) {
    if(test_scheduler("binlpt", name))
			return do_work<0>();
    throw std::string("[MOGSLib] Invalid scheduler name.");
  }
};

}