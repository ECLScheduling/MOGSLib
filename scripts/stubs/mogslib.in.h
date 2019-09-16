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
  inline static void do_work(){
    std::get<i>(schedulers).work(std::get<i>(contexts));
  }

  inline static bool test_scheduler(const std::string &schedname, const std::string &name){
    return schedname.compare(name) == 0;
  }

  inline static void work(const std::string &name) {
    $SCHED_WORK_SNIPPETS$
    else {
      throw std::string("[MOGSLib] Invalid scheduler name.");
    }
  }
};

}