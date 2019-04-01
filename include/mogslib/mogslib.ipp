#ifdef OMP_RTS_INCLUDED
#include <abstractions/rts/openmp/openmp.ipp>
#endif

#ifdef CHARM_RTS_INCLUDED
#include <abstractions/rts/charm/charm.ipp>
#endif

namespace MOGSLib {

API::Schedulers API::schedulers;

template<unsigned i>
inline typename MOGSLib::Config::Policy<typename Traits::Id>::Schedule API::do_work() {
  return std::get<i>(schedulers).work(std::get<i>(schedulers));
}


inline bool API::test_scheduler(const std::string &schedname, const std::string &name) {
  return !name.compare(schedname);
}

}