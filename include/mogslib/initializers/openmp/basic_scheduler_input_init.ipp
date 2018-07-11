BEGIN_NAMESPACE(Abstraction)
decltype(Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput>::task_loads) Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput>::task_loads = nullptr;
decltype(Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput>::ntasks) Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput>::ntasks = 0;

void Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput>::cleanup() {
  if(task_loads != nullptr) {
    delete [] task_loads;
    task_loads = nullptr;
  }
}

void Initializer<RuntimeSystemEnum::OpenMP, Adapter::BasicSchedulerInput>::init(ConcreteAdapter *adapter) {
  assert((task_loads != nullptr) && "Initializer<OpenMP, BasicSchedulerInput> must be fed with task load values from the user. Initialize the struct static variable 'task_loads'.");
  
  adapter->tasks.resize(ntasks);
  std::memcpy(adapter->tasks.data(), task_loads, sizeof(Load) * ntasks);

  adapter->PEs.resize(RTS<targetRTS>::nPEs);
  std::memset(adapter->tasks.data(), 0, sizeof(Load) * ntasks);
}

END_NAMESPACE