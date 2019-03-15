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
  return std::get<i>(schedulers).work();
}

namespace Context {
  decltype(OmpDelayTest::_input) OmpDelayTest::_input;
}

}