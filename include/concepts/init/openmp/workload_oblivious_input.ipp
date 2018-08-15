BEGIN_NAMESPACE(Concept)

template<>
void WorkloadObliviousInput::init<MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP>() {
  tasks = MOGSLib::RTS::OpenMP::ntasks;
  adapter->PEs = MOGSLib::RTS::OpenMP::nPEs;
}

END_NAMESPACE