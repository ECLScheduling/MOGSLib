#include <gtest/gtest.h>

#include "mock/custom_traits.h"

#include <rts/charm/charm.h>
#include <rts/charm/charm.ipp>

using Load = decltype(BaseLB::ProcStats::bg_walltime);
using Index = decltype(BaseLB::LDStats::count);
using Speed = decltype(BaseLB::ProcStats::pe_speed);

using Traits = CustomCharmTraits<true,true>;
using Charm = MOGSLib::RTS::Charm<Traits>;

struct Chare {
  bool migratable;
  Load wallTime;
  Index from_proc;

  Chare(){}
  Chare(const bool &mig, const Load &walltime, const Index &proc) : migratable(mig),  wallTime(walltime), from_proc(proc) {}
};

struct PU {
  bool available;
  int pe_speed;
  Load bg_walltime;

  PU(){}
  PU(const bool &avail, const int &speed, const Load &bg_time) : available(avail), pe_speed(speed), bg_walltime(bg_time) {}
};

class CharmWorkloadFunctionalitiesTest : public ::testing::Test {
public:
  std::unique_ptr<BaseLB::LDStats> stats;

  void SetUp() {
    stats = std::make_unique<BaseLB::LDStats>();
    Charm::stats = stats.get();
  }

  void make_pus(const unsigned &n) {
    stats->count = n;
    stats->procs = std::make_unique<BaseLB::ProcStats[]>(n);
  }

  void set_pus(const std::vector<PU> &pus) {
    make_pus(pus.size());

    auto i = 0;
    for(auto pu : pus) {
      stats->procs[i].available = pu.available;
      stats->procs[i].pe_speed = pu.pe_speed;
      stats->procs[i++].bg_walltime = pu.bg_walltime;
    }
  }

  void make_chares(const unsigned &n) {
    stats->n_objs = n;
    stats->objData = std::make_unique<BaseLB::LDObjData[]>(n);
    stats->from_proc = std::make_unique<Index[]>(n);
  }

  void set_chares(const std::vector<Chare> &chares) {
    make_chares(chares.size());

    auto i = 0;
    for(auto chare : chares) {
      stats->objData[i].wallTime = chare.wallTime;
      stats->objData[i].migratable = chare.migratable;
      stats->from_proc[i++] = chare.from_proc;
    }
  }

  auto predict_chare_load() {
    Charm::LBDB::Chare::count();
    return Charm::LBDB::Chare::load_prediction();
  }

  auto predict_pus_load() {
    Charm::LBDB::Chare::count();
    Charm::LBDB::PU::count();

    return Charm::LBDB::PU::load_prediction();
  }
};

/** Charm++ chares workload prediction based on load walltime and pe speed. **/

// Basic check
TEST_F(CharmWorkloadFunctionalitiesTest, chare_load_is_calculated_using_walltime) {
  std::vector<PU> pus {PU(true, 1, 0)}; // One PU with 1 pe_speed and 0 background walltime.
  std::vector<Chare> chares {Chare(true, 2, 0)}; // One chare with load 2 that is assigned to PU 0 and is migratable.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();

  ASSERT_EQ(2, loads[0]); // walltime is 2 and pe_speed is 1. Total chare load is 2.
}

// Check for different PUs
TEST_F(CharmWorkloadFunctionalitiesTest, chare_load_depends_on_pe_speed) {
  std::vector<PU> pus {PU(true, 2, 0), PU(true, 3, 0)}; // Two PUs, both with 0 background wall time and available. First with 2 speed and the latter with 3.
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 1)}; // Two chares, both with 2 walltime load, assigned to PU 0 and 1 respectively.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();

  ASSERT_EQ(4, loads[0]); // walltime is 2 and pe_speed is 2. Total chare load is 4.
  ASSERT_EQ(6, loads[1]); // walltime is 2 and pe_speed is 3. Total chare load is 6.
}

// Unmigrateable chares are/not accounted for when check_for_fixed_chares is inactive/active.
/**
 * \brief TODO: This test must be issued in different "check_for_fixed_chares" values in system/traits. There must be more flexibility for this test to be automated.
 */
TEST_F(CharmWorkloadFunctionalitiesTest, chares_can_be_unmigratable) {
  std::vector<PU> pus {PU(true, 2, 0), PU(true, 3, 0)}; // Two PUs, both with 0 background wall time and available. First with 2 speed and the latter with 3.
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(true, 2, 1)}; // First chare is unmigratable
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();
  auto expected_size = (Traits::check_for_fixed_chares)? 1 : 2;
  
  ASSERT_EQ(expected_size, loads.size());

  if(Traits::check_for_fixed_chares)
    ASSERT_EQ(6, loads[0]); // Only the second chare is accounted for.
  else {
    ASSERT_EQ(4, loads[0]); // The functionality doesnt check for the migratable status and evaluates first chare as migratable.
    ASSERT_EQ(6, loads[1]); // walltime is 2 and pe_speed is 3. Total chare load is 6.
  }
}

/** Charm++ PUs workload prediction based on load walltime and pe speed. **/

TEST_F(CharmWorkloadFunctionalitiesTest, pu_workload_is_its_background_walltime) {
  std::vector<PU> pus {PU(true, 1, 1), PU(true, 1, 2)};
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 0)};
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(pus[i].bg_walltime, loads[i]);
}

TEST_F(CharmWorkloadFunctionalitiesTest, pu_workload_is_normalized_by_its_speed) {
  std::vector<PU> pus {PU(true, 1, 2), PU(true, 2, 2)};
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 0)};
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(pus[i].bg_walltime * pus[i].pe_speed, loads[i]);
}

//TODO: This test must be compiled and run with differents values for the 'check_for_fixed_chares' Charm++ traits.
TEST_F(CharmWorkloadFunctionalitiesTest, pu_workload_might_accounts_for_fixed_tasks) {
  std::vector<PU> pus {PU(true, 1, 2), PU(true, 2, 2)};
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(false, 2, 1)}; // Tasks are unmigratable with walltime load 2.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  // The expected load depends if Charm++ traits dictates that there ARE unmigratable tasks.
  auto expected_loads = [](auto pu, auto hosted_chare) {
    auto pu_load = pu.pe_speed * pu.bg_walltime;
    return (Traits::check_for_fixed_chares)? pu_load + hosted_chare.wallTime * pu.pe_speed : pu_load; };

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(expected_loads(pus[i], chares[i]), loads[i]);
}

//TODO: This test must be compiled and run with differents values for the 'check_for_unavailable_pus' Charm++ traits.
TEST_F(CharmWorkloadFunctionalitiesTest, pu_workload_might_not_consider_unavailable_pus) {
  std::vector<PU> pus {PU(false, 1, 2), PU(true, 2, 2)}; // First PU is unavailable.
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 1)};
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();
  auto expected_loads = [](auto pu) { return pu.pe_speed * pu.bg_walltime; };
  auto expected_size = (Traits::check_for_unavailable_pus)? 1 : 2;

  ASSERT_EQ(expected_size, loads.size());
  if(Traits::check_for_unavailable_pus)
    EXPECT_EQ(expected_loads(pus[1]), loads[0]);
  else {
    EXPECT_EQ(expected_loads(pus[0]), loads[0]);
    EXPECT_EQ(expected_loads(pus[1]), loads[1]);
  }
}