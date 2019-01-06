#pragma once

#include <structures/input/workload_aware.h>

#include <abstractions/rts/openmp/openmp.h>
#include <omp.h>

namespace MOGSLib { namespace Context {

struct OpenMPBase {
  using Id = typename Traits::Id;
  using Load = typename Traits::Load;

  struct Input {
    Load *tasks = nullptr;
    Load *pus = nullptr;
    Id n_tasks, n_pus;

    virtual ~Input() {
      if(tasks){
        delete [] tasks;
        tasks = nullptr;
      }
      if(pus){
        delete [] pus;
        pus = nullptr;
      }
    }

    inline void alloc_pu_workloads(const Id &n) {
      n_pus = n;
      if(!pus)
        pus = new Load[n]();
    }

    inline void alloc_task_workloads(const Id &n) {
      n_tasks = n;
      if(!tasks)
        tasks = new Load[n]();
    }

    inline auto task_workloads() { return tasks; }

    inline auto ntasks() { return n_tasks; }

    inline auto pu_workloads() { return pus; }

    inline auto npus() { return n_pus; }
  };

  Input _input;

  inline void set_iterations(const Id &n) {
    _input.alloc_task_workloads(n);
    omp_set_taskmap_size(n);
  }

  inline auto& input() {
    _input.alloc_pu_workloads(MOGSLib::RTS::OpenMP::threads);
    return _input;
  }

  inline auto k() { return MOGSLib::RTS::OpenMP::chunks;  }
};

}}