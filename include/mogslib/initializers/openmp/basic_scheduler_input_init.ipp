BEGIN_NAMESPACE(Abstraction)

void Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput>::init(ConcreteAdapter *adapter) {
  adapter->tasks.resize(RTS<targetRTS>::ntasks);
  adapter->PEs.resize(RTS<targetRTS>::nPEs);
}

END_NAMESPACE