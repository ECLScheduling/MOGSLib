#pragma once

#include <memory>

namespace BaseLB {

/**
 * \brief A mock structure with the same data signature as its counterpart in Charm 6.9.0.
 * @details This should be solely used for syntax tests sice it does not mock Charm++ functionalities.
 */
struct ProcStats {  // per processor
  double total_walltime;
  double total_cputime;
  double idletime;
  double bg_walltime;
  double bg_cputime;
  int pe_speed;
  double utilization;
  bool available = false;
  int   n_objs;
};

struct LDObjData {
  bool migratable = false;
  double wallTime;
};

/**
 * \brief This structure is not yet used in any balancer.
 */
struct LDCommData {};

/**
 * \brief A mock structure with the same data signature as its counterpart in Charm 6.9.0.
 * @details This should be solely used for syntax tests sice it does not mock Charm++ functionalities.
 */
struct LDStats { // load balancing database
  std::unique_ptr<ProcStats[]> procs;
  int count;

  unsigned nprocs() { return count; }

  int   n_objs;
  int   n_migrateobjs;
  std::unique_ptr<LDObjData[]> objData;

  int   n_comm;
  std::unique_ptr<LDCommData[]> commData;

  std::unique_ptr<int[]> from_proc, to_proc;
};

}