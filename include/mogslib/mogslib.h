#pragma once
#include <iostream>
#include <tuple>
#include <string>

#include <abstractions/traits/lulesh2.h>
namespace MOGSLib {  using Traits = Lulesh2;  }

#include <abstractions/context/omp_lulesh2.h>

#include <schedulers/binlpt.h>

namespace MOGSLib {

struct API {
  using Contexts = std::tuple<Context::Lulesh2>;
  using Schedulers = std::tuple<Scheduler::BinLPT<typename std::tuple_element<0, Contexts>::type>>;

  static Contexts contexts;
  static Schedulers schedulers;

  template<unsigned i>
  inline static typename std::tuple_element<i, Schedulers>::type::Ctx& get_sched_ctx() { throw "Invalid Scheduler Index"; }

  template<unsigned i>
  inline static typename MOGSLib::Config::Policy<typename Traits::Id>::Schedule do_work();

  inline static auto work(const std::string &name) {
    if(!name.compare(std::string("binlpt")))
      return do_work<0>();
    throw "Invalid scheduler name.";
  }
};

API::Contexts API::contexts;
API::Schedulers API::schedulers;

}

namespace MOGSLib {

template<>
inline typename std::tuple_element<0, API::Schedulers>::type::Ctx& API::get_sched_ctx<0>() { return std::get<0>(API::contexts); }

template<unsigned i>
inline typename MOGSLib::Config::Policy<typename Traits::Id>::Schedule API::do_work() {
  return std::get<i>(schedulers).work(get_sched_ctx<i>());
}

}