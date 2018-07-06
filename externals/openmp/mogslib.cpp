#ifdef LINKED_TO_OMP

#include <mogslib/rts/openmp.h>

#include <schedulers/round_robin.h>
#include <mogslib/initializers/charm/basic_scheduler_input_init.h>

/**
 * @brief Set the amount of chunks in the OpenMP RTS datastructure.
 * @details A C++ proxy function to set the chunksize data in OpenMP.
 * @param chunksize The amount of chunks generated in OpenMP.
 */
inline void mogslib_call_set_chunksize(unsigned chunksize) {
  MOGSLib::OpenMP_RTS::set_chunk_size(chunksize);
}

/**
 * @brief Set the amount of chunks in the OpenMP RTS datastructure.
 * @details A C++ proxy function to set the chunksize data in OpenMP.
 * @param chunksize The amount of chunks generated in OpenMP.
 */
inline void mogslib_call_set_nPEs(unsigned nPEs) {
  MOGSLib::OpenMP_RTS::set_nPEs(nPEs);
}

/**
 * @brief Call the scheduler within MOGSLib to obtain a task map.
 * @details A C++ proxy function to call the selected MOGSLib scheduler.
 * @return The task map represented as an array to where the task should execute.
 */
inline unsigned *mogslib_call_strategy_map() {
  // Declare scheduler
  static auto OpenMPEnumVal = MOGSLib::Abstraction::RuntimeSystemEnum::OpenMP;
  using OpenMPRTS = MOGSLib::Abstraction::RTS<OpenMPEnumVal>;

  template<typename T>
  using Initializer = MOGSLib::Abstraction::Initializer<OpenMPEnumVal, T>;

  template<typename T>
  using Binder = MOGSLib::Abstraction::Binder<T>;

  using ConcreteAdapter = MOGSLib::Adapter::BasicSchedulerInput;
  using Scheduler = MOGSLib::Scheduler::RoundRobin<ConcreteAdapter>;

  Scheduler scheduler;

  // Declare and instantiate concrete adapters
  auto basic_input = new ConcreteAdapter();

  // Initialize concrete adapters
  Initializer<ConcreteAdapter>::init(basic_input);

  // Bind concrete adapters to concepts.
  Binder<Scheduler>::bind(basic_input, basic_input);

  return scheduler.work();
}

extern "C" {

/**
 * @brief A function to interface with MOGSLib to register the amount of chunks in OpenMP.
 * @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
void mogslib_set_chunksize(unsigned chunksize) {
  mogslib_call_set_chunksize(chunksize);
}

/**
 * @brief A function to interface with MOGSLib to register the amount of PEs in OpenMP.
 * @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
void mogslib_set_nPEs(unsigned nPEs) {
  mogslib_call_set_nPEs(nPEs);
}

/**
 * @brief A function to interface with MOGSLib to call the scheduler task mapping.
 * @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
unsigned *mogslib_strategy_map() {
  return mogslib_call_strategy_map();
}

}

#endif // RTS_IS_OPENMP