#pragma once

#include <tuple>
#include <string>

#include <abstractions/traits/libgomp_default.h>

namespace MOGSLib {  using Traits = LibgompDefault;  }

#include <abstractions/contexts/libgomp.h>

#include <model/schedulers/binlpt.h>
#include <model/schedulers/greedy.h>

#include "macros.h"

namespace MOGSLib {

struct API {
  using Contexts = std::tuple<Ctx(LibGOMP), Ctx(LibGOMP)>;
  using Schedulers = std::tuple<Sched(BinLPT, 0), Sched(Greedy, 1)>;

  static Contexts contexts;
  static Schedulers schedulers;

  template<unsigned i>
  inline static void do_work(){
    std::get<i>(schedulers).work(std::get<i>(contexts));
  }

  inline static bool test_scheduler(const std::string &schedname, const std::string &name){
    return schedname.compare(name) == 0;
  }

  inline static void work(const std::string &name) {
	if(test_scheduler("binlpt", name)) {
		do_work<0>();
		return;
	}
	if(test_scheduler("greedy", name)) {
		do_work<1>();
		return;
	}
    throw std::string("[MOGSLib] Invalid scheduler name: " + name);
  }
};

}