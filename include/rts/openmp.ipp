namespace MOGSLib { namespace Abstraction {
decltype(RTS<RuntimeSystemEnum::OpenMP>::chunk_size) RTS<RuntimeSystemEnum::OpenMP>::chunk_size = 0;
decltype(RTS<RuntimeSystemEnum::OpenMP>::nPEs) RTS<RuntimeSystemEnum::OpenMP>::nPEs = 0;
decltype(RTS<RuntimeSystemEnum::OpenMP>::ntasks) RTS<RuntimeSystemEnum::OpenMP>::ntasks = 0;
decltype(RTS<RuntimeSystemEnum::OpenMP>::get_task_loads) RTS<RuntimeSystemEnum::OpenMP>::get_task_loads = nullptr;
decltype(RTS<RuntimeSystemEnum::OpenMP>::get_PE_loads) RTS<RuntimeSystemEnum::OpenMP>::get_PE_loads = nullptr;
}}