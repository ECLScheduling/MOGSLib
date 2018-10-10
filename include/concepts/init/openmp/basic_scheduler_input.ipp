BEGIN_NAMESPACE(Concept)

template<>
void BasicSchedulerInput::init<MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP>() {
  tasks.resize(MOGSLib::RTS::OpenMP::ntasks);
  PEs.resize(MOGSLib::RTS::OpenMP::nPEs);
}

END_NAMESPACE