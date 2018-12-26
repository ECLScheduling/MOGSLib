namespace MOGSLib { namespace Context {
template<typename I, typename L>
MOGSLib::Input::WorkloadAware<I, L> WorkloadAware<I, L>::_input;

template<typename I, typename L>
I WorkloadAware<I, L>::_k = 1;
}}