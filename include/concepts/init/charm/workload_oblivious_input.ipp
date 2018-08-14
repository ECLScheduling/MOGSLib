BEGIN_NAMESPACE(Concept)

template<>
void WorkloadObliviousInput::init<MOGSLib::Abstraction::RuntimeSystemEnum::Charm>() {
  auto input = MOGSLib::RTS::Charm::stats;

  tasks = input->n_objs;
  PEs = input->nprocs();
}

END_NAMESPACE