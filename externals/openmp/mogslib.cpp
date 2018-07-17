// #### MOGSLib Includes ####

// MOGSLib RTS data
#include <mogslib/rts/openmp.h>
#include <mogslib/rts/openmp.ipp>

// MOGSLib Scheduling Strategies
#include <schedulers/round_robin.h>
#include <mogslib/binders/round_robin_binder.h>

// MOGSLib Concrete Adapters
#include <mogslib/initializers/openmp/workload_oblivious_input_init.h>

// #### End of MOGSLib Includes ####

struct MOGSLibDefinitions {
  using RTS = MOGSLib::RTS::OpenMP;
  static constexpr auto system = RTS::SystemVal;

  template<typename T>
  using Initializer = MOGSLib::Abstraction::Initializer<system, T>;

  template<typename T>
  using Binder = MOGSLib::Abstraction::Binder<T>;

  using ConcreteAdapter = MOGSLib::Adapter::WorkloadObliviousInput;
  using Scheduler = MOGSLib::Scheduler::RoundRobin<ConcreteAdapter>;
};

/**
 * @brief Set the amount of chunks in the OpenMP RTS datastructure.
 * @details A C++ proxy function to set the chunksize data in OpenMP.
 * @param chunksize The amount of chunks generated in OpenMP.
 */
inline void mogslib_call_set_chunksize(unsigned chunksize) {
  MOGSLibDefinitions::RTS::set_chunk_size(chunksize);
}

/**
 * @brief Set the amount of chunks in the OpenMP RTS datastructure.
 * @details A C++ proxy function to set the chunksize data in OpenMP.
 * @param chunksize The amount of chunks generated in OpenMP.
 */
inline void mogslib_call_set_nPEs(unsigned nPEs) {
  MOGSLibDefinitions::RTS::set_nPEs(nPEs);
}

/**
 * @brief Set the amount of tasks in the OpenMP RTS datastructure.
 * @details A C++ proxy function to set the ntasks data in OpenMP.
 * @param ntasks The amount of tasks generated in OpenMP.
 */
inline void mogslib_call_set_ntasks(unsigned ntasks) {
  MOGSLibDefinitions::RTS::set_ntasks(ntasks);
}

/**
 * @brief Call the scheduler within MOGSLib to obtain a task map.
 * @details A C++ proxy function to call the selected MOGSLib scheduler.
 * @return The task map represented as an array to where the task should execute.
 */
inline unsigned *mogslib_call_strategy_map() {
  // Declare scheduler
  MOGSLibDefinitions::Scheduler scheduler;

  // Declare and instantiate concrete adapters
  auto basic_input = new MOGSLibDefinitions::ConcreteAdapter();

  // Initialize concrete adapters
  MOGSLibDefinitions::Initializer<MOGSLibDefinitions::ConcreteAdapter>::init(basic_input);

  // Bind concrete adapters to concepts.
  MOGSLibDefinitions::Binder<MOGSLibDefinitions::Scheduler>::bind(basic_input, basic_input);

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
 * @brief A function to interface with MOGSLib to register the amount of tasks in OpenMP.
 * @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
void mogslib_set_ntasks(unsigned ntasks) {
  mogslib_call_set_ntasks(ntasks);
}

/**
 * @brief A function to interface with MOGSLib to call the scheduler task mapping.
 * @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
unsigned *mogslib_strategy_map() {
  return mogslib_call_strategy_map();
}

}