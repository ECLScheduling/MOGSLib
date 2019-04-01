#include <mogslib/mogslib.h>
#include <mogslib/mogslib.ipp>

#include <iostream>

unsigned *arr = nullptr;

/**
 *  @brief Set the amount of chunks in the OpenMP RTS datastructure.
 *  @details A C++ proxy function to set the chunksize data in OpenMP.
 *  @param chunksize The amount of chunks generated in OpenMP.
 */
inline void mogslib_call_set_chunksize(unsigned n) {
  MOGSLib::RTS::OpenMP::nchunks(n);
}

/**
 *  @brief Set the amount of chunks in the OpenMP RTS datastructure.
 *  @details A C++ proxy function to set the chunksize data in OpenMP.
 *  @param chunksize The amount of chunks generated in OpenMP.
 */
inline void mogslib_call_set_npus(unsigned n) {
  MOGSLib::RTS::OpenMP::nthreads(n);
}

/**
 *  @brief Call the scheduler within MOGSLib to obtain a task map.
 *  @details A C++ proxy function to call the selected MOGSLib scheduler.
 *  @return The task map represented as an array to where the task should execute.
 */
inline unsigned *mogslib_call_strategy_map() {
  std::string strategy = "binlpt"; //TODO: Change here to add the strategy or call a custom function.
  try {
    auto schedule = MOGSLib::API::work(strategy);
    if(arr != nullptr) {
      delete [] arr;
      arr = nullptr;
    }
    arr = new unsigned[schedule.size()];
    
    std::copy(schedule.begin(), schedule.end(), arr);
    return arr;
  } catch (std::string n) {
    std::cout << n << std::endl;
    exit(1);
  }
}

extern "C" {

/**
 *  @brief A function to interface with MOGSLib to register the amount of chunks in OpenMP.
 *  @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
void mogslib_set_chunksize(unsigned chunksize) {
  mogslib_call_set_chunksize(chunksize);
}

/**
 *  @brief A function to interface with MOGSLib to register the amount of PEs in OpenMP.
 *  @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
void mogslib_set_npus(unsigned npus) {
  mogslib_call_set_npus(npus);
}

/**
 *  @brief A function to interface with MOGSLib to call the scheduler task mapping.
 *  @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
unsigned *mogslib_strategy_map() {
  return mogslib_call_strategy_map();
}

}