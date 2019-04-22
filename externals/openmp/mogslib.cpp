#include <mogslib/mogslib.h>
#include <mogslib/mogslib.ipp>

#include <iostream>


namespace MOGSLib { namespace ConnectionLayer {
unsigned *array = nullptr;
unsigned allocated_size = 0;
}}
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
  
  std::string strategy = "buffered_binlpt"; //TODO: Change here to call another strategy (you may call functions to change it dynamically).

  try {
    auto schedule = MOGSLib::API::work(strategy);
    auto schedule_size = schedule.size();

    // Checks if the previously allocated array can store the new schedule data. If it cannot, free the memory of the previous one.
    if(MOGSLib::ConnectionLayer::array != nullptr && MOGSLib::ConnectionLayer::allocated_size < schedule_size) {
      delete [] array;
      MOGSLib::ConnectionLayer::array = nullptr;
    }
    // Checks if the array is not allocated. If it is not, allocate a new one to hold the schedule.
    if(MOGSLib::ConnectionLayer::array == nullptr) {
      array = new unsigned[schedule_size];
      MOGSLib::ConnectionLayer::allocated_size = schedule_size;
    }
    
    // Copy the contents of the schedule into the array and pass it to LibGOMP.
    std::copy(schedule.begin(), schedule.end(), MOGSLib::ConnectionLayer::array);
    return MOGSLib::ConnectionLayer::array;

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