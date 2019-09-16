#ifdef OMP_RTS_INCLUDED
#include <abstractions/rts/openmp/openmp.ipp>
#endif

#ifdef CHARM_RTS_INCLUDED
#include <abstractions/rts/charm/charm.ipp>
#endif

namespace MOGSLib {

API::Schedulers API::schedulers;
API::Contexts API::contexts;

}