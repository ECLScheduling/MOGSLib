#include <structures/input/base.h>

namespace MOGSLib { namespace Functionality {

template<typename I>
inline void OpenMPInputFetch::fetch<MOGSLib::Input::Base<I>>(MOGSLib::Input::Base &input) {
  input.pus = nthreads;
};

template<typename I, typename L>
inline void OpenMPInputFetch::fetch<MOGSLib::Input::WorkloadAware<I,L>>(MOGSLib::Input::WorkloadAware<I,L> &input) {
  input.pus.resize(nthreads);
};

}}