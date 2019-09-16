#include <iostream>
#include <vector>
#include <random>

#include <omp.h>
#include <model/policies/binlpt.h>

#ifndef N
#define N 27000
#endif

/**
 *  @brief Call the scheduler within MOGSLib to obtain a task map.
 *  @details A C++ proxy function to call the selected MOGSLib scheduler.
 *  @return The task map represented as an array to where the task should execute.
 */
inline unsigned *mogslib_call_strategy_map(unsigned *tasks, unsigned ntasks, unsigned nthreads, unsigned nchunks) {
  return MOGSLib::Policy::BinLPT::work(tasks, ntasks, nthreads, nchunks);
}

extern "C" {

/**
 *  @brief A function to interface with MOGSLib to call the scheduler task mapping.
 *  @details A C function to interface with OpenMP and direct the execution flow back to C++.
 */
unsigned *mogslib_strategy_map(unsigned *tasks, unsigned ntasks, unsigned nthreads, unsigned nchunks) {
  return mogslib_call_strategy_map(tasks, ntasks, nthreads, nchunks);
}

bool mogslib_has_persistent_taskmap() {
  return false;
}

}

auto set_loads() {
  std::mt19937 gen(42); //Standard mersenne_twister_engine seeded with 42
  std::uniform_int_distribution<> dis(1, 8);

  std::vector<unsigned> loads = std::vector<unsigned>(N);

  for(auto i = 0; i < N; ++i)
    loads[i] = dis(gen);

  return loads;
}

void set_values(std::vector<unsigned> &a, std::vector<unsigned> &b) {
  std::mt19937 gen(24); //Standard mersenne_twister_engine seeded with 42
  std::uniform_int_distribution<> dis(1, 10);

  a = std::vector<unsigned>(N);
  b = std::vector<unsigned>(N);

  for(auto i = 0; i < N; ++i) {
    a[i] = dis(gen);
    b[i] = dis(gen);
  }

}

int main() {
  auto loads = set_loads();

  std::vector<unsigned> a,b,c;
  set_values(a,b);
  c = std::vector<unsigned>(N);

  omp_set_workload(loads.data(), loads.size());
  #pragma omp parallel for schedule(runtime)
  for(auto i = 0; i < N; ++i)
    c[i] = a[i] * b[i];

  return 0;
}