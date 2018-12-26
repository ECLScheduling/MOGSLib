#include <gtest/gtest.h>

#include "mock/custom_traits.h"

#include <rts/charm/charm.h>
#include <rts/charm/charm.ipp>

using Load = decltype(BaseLB::ProcStats::bg_walltime);
using Id = decltype(BaseLB::LDStats::count);
using Speed = decltype(BaseLB::ProcStats::pe_speed);

/**
 *  @brief Testing structure to express a mock of a Charm's chare structure.
 */
struct Chare {
  bool migratable;
  Load wallTime;
  Id from_proc;

  /// @brief Constructs an empty chare mock.
  Chare(){}

  /**
   *  @brief Constructs a chare mock with all its relevant data.
   *  @param mig Whether the chare is migratable or not.
   *  @param walltime How much time it took last iteration to be computed.
   *  @param proc The id of the current PU hosting this chare.
   */
  Chare(const bool &mig, const Load &walltime, const Id &proc) : migratable(mig),  wallTime(walltime), from_proc(proc) {}
};

/**
 *  @brief Testing structure to express a mock of a Charm's PU structure.
 */
struct PU {
  bool available;
  int pe_speed;
  Load bg_walltime;

  /// @brief Constructs an empty PU mock.
  PU(){}

  /**
   *  @brief Constructs a PU mock with all its relevant data.
   *  @param avail Whether the PU is available or not.
   *  @param speed A numeric value to represent its processing speed.
   *  @param bg_time The amount of time spent with processing background tasks.
   */
  PU(const bool &avail, const int &speed, const Load &bg_time) : available(avail), pe_speed(speed), bg_walltime(bg_time) {}
};

/**
 *  @class CharmWorkloadFunctionalitiesTest
 *  @brief Base test class for workload functionalities of the LBDB structure in Charm++
 *  @tparam AA Express if functionalities are aware of PUs availability.
 *  @tparam MA Express if functionalities are awawre of chares migratability.
 */
template<bool AA, bool MA>
class CharmWorkloadFunctionalitiesTest {
public:
  using Traits = CustomCharmTraits<AA, MA>;
  using Charm = MOGSLib::RTS::Charm<Traits>;

  /// @brief A pointer to the mocked stats structure.
  std::unique_ptr<BaseLB::LDStats> stats;

  /// @brief Set up the tests by creating a stats instance and assigning it to the RTS abstraction.
  void SetUp() {
    stats = std::make_unique<BaseLB::LDStats>();
    Charm::stats = stats.get();
  }

  /**
   *  @brief Allocates the PUs in the stats structure.
   *  @param n The amount of PUs in the simulated platform.
   */
  void make_pus(const unsigned &n) {
    stats->count = n;
    stats->procs = std::make_unique<BaseLB::ProcStats[]>(n);
  }

  /**
   *  @brief Sets the PU data in the simulated platform.
   *  @param pus A vector of PU simplified abstractions to be inserted in stats.
   */
  void set_pus(const std::vector<PU> &pus) {
    make_pus(pus.size());

    auto i = 0;
    for(auto pu : pus) {
      stats->procs[i].available = pu.available;
      stats->procs[i].pe_speed = pu.pe_speed;
      stats->procs[i++].bg_walltime = pu.bg_walltime;
    }
  }

  /**
   *  @brief Allocate the chares in the stat structure.
   *  @param n The amount chares in the simulated application.
   */
  void make_chares(const unsigned &n) {
    stats->n_objs = n;
    stats->objData = std::make_unique<BaseLB::LDObjData[]>(n);
    stats->from_proc = std::make_unique<Id[]>(n);
  }

  /**
   *  @brief Sets the chare data in the simulated application.
   *  @param chares A vector of chare simplified abstractions to be inserted in stats.
   */
  void set_chares(const std::vector<Chare> &chares) {
    make_chares(chares.size());

    auto i = 0;
    for(auto chare : chares) {
      stats->objData[i].wallTime = chare.wallTime;
      stats->objData[i].migratable = chare.migratable;
      stats->from_proc[i++] = chare.from_proc;
    }
  }

  /**
   *  @brief Proxy method to call the load_prediction method for chares in Charm++ after calling count.
   *  Calling count before load_prediction is a necessity as pointed out in its class documentation.
   */
  auto predict_chare_load() {
    Charm::LBDB::Chare::count();
    return Charm::LBDB::Chare::load_prediction();
  }

  /**
   *  @brief Proxy method to call the load_prediction method for PUs in Charm++ after calling count.
   *  Calling count before load_prediction is a necessity as pointed out in its class documentation.
   */
  auto predict_pus_load() {
    Charm::LBDB::Chare::count();
    Charm::LBDB::PU::count();

    return Charm::LBDB::PU::load_prediction();
  }
};

/**
 *  @class WorkloadFullyAwareTest
 *  @brief Test class for counting functionalities of the LBDB structure in Charm++ that is aware of unmigratable chares and unavailable processors.
 */
class WorkloadFullyAwareTest : public CharmWorkloadFunctionalitiesTest<true,true>, public ::testing::Test {
  /// @brief SetUp should call its base class implementation.
  void SetUp() {  CharmWorkloadFunctionalitiesTest<true,true>::SetUp();  }
};

/**
 *  @class WorkloadFullyUnawareTest
 *  @brief Test class for counting functionalities of the LBDB structure in Charm++ that is not aware of unmigratable chares neither of unavailable processors.
 */
class WorkloadFullyUnawareTest : public CharmWorkloadFunctionalitiesTest<false,false>, public ::testing::Test {
  /// @brief SetUp should call its base class implementation.
  void SetUp() {  CharmWorkloadFunctionalitiesTest<false,false>::SetUp();  }
};

/**
 *  @class WorkloadAvailabilityAwareTest
 *  @brief Test class for counting functionalities of the LBDB structure in Charm++ that is unaware of unmigratable chares but aware of unavailable processors.
 */
class WorkloadAvailabilityAwareTest : public CharmWorkloadFunctionalitiesTest<true,false>, public ::testing::Test {
  /// @brief SetUp should call its base class implementation.
  void SetUp() {  CharmWorkloadFunctionalitiesTest<true,false>::SetUp();  }
};

/**
 *  @class WorkloadMigratabilityAwareTest
 *  @brief Test class for counting functionalities of the LBDB structure in Charm++ that is aware of unmigratable chares but not of unavailable processors.
 */
class WorkloadMigratabilityAwareTest : public CharmWorkloadFunctionalitiesTest<false,true>, public ::testing::Test {
  /// @brief SetUp should call its base class implementation.
  void SetUp() {  CharmWorkloadFunctionalitiesTest<false,true>::SetUp();  }
};


/**
 *  @brief Chare load will be its walltime if its speed is 1.
 */
TEST_F(WorkloadFullyAwareTest, chare_load_is_calculated_using_walltime) {
  std::vector<PU> pus {PU(true, 1, 0)}; // One PU with 1 pe_speed and 0 background walltime.
  std::vector<Chare> chares {Chare(true, 2, 0)}; // One chare with load 2 that is assigned to PU 0 and is migratable.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();

  ASSERT_EQ(2, loads[0]); // walltime is 2 and pe_speed is 1. Total chare load is 2.
}

/**
 *  @brief Chare load depends on the pe_speed of the host processor multiplicated by the walltime.
 */
TEST_F(WorkloadFullyAwareTest, chare_load_depends_on_pe_speed) {
  std::vector<PU> pus {PU(true, 2, 0), PU(true, 3, 0)}; // Two PUs, both with 0 background wall time and available. First with 2 speed and the latter with 3.
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 1)}; // Two chares, both with 2 walltime load, assigned to PU 0 and 1 respectively.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();

  ASSERT_EQ(4, loads[0]); // walltime is 2 and pe_speed is 2. Total chare load is 4.
  ASSERT_EQ(6, loads[1]); // walltime is 2 and pe_speed is 3. Total chare load is 6.
}

/**
 *  @brief Unmigratable chares are not accounted for on fully aware implementations
 */
TEST_F(WorkloadFullyAwareTest, unmigratable_chares_are_not_accounted) {
  std::vector<PU> pus {PU(true, 2, 0), PU(true, 3, 0)}; // Two PUs, both with 0 background wall time and available. First with 2 speed and the latter with 3.
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(true, 2, 1)}; // First chare is unmigratable
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();
  ASSERT_EQ(6, loads[0]); // Only the second chare is accounted for.
}

/**
 *  @brief Unmigratable chares are not accounted for on migratability aware implementations
 */
TEST_F(WorkloadMigratabilityAwareTest, unmigratable_chares_are_not_accounted) {
  std::vector<PU> pus {PU(true, 2, 0), PU(true, 3, 0)}; // Two PUs, both with 0 background wall time and available. First with 2 speed and the latter with 3.
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(true, 2, 1)}; // First chare is unmigratable
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();
  ASSERT_EQ(6, loads[0]); // Only the second chare is accounted for.
}

/**
 *  @brief Unmigratable chares are accounted for on migratability unaware implementations
 */
TEST_F(WorkloadAvailabilityAwareTest, unmigratable_chares_are_not_accounted) {
  std::vector<PU> pus {PU(true, 2, 0), PU(true, 3, 0)}; // Two PUs, both with 0 background wall time and available. First with 2 speed and the latter with 3.
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(true, 2, 1)}; // First chare is unmigratable
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();
  ASSERT_EQ(4, loads[0]);
  ASSERT_EQ(6, loads[1]);
}

/**
 *  @brief Unmigratable chares are accounted for on fully unaware implementations
 */
TEST_F(WorkloadFullyUnawareTest, unmigratable_chares_are_not_accounted) {
  std::vector<PU> pus {PU(true, 2, 0), PU(true, 3, 0)}; // Two PUs, both with 0 background wall time and available. First with 2 speed and the latter with 3.
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(true, 2, 1)}; // First chare is unmigratable
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_chare_load();
  ASSERT_EQ(4, loads[0]); // Only the second chare is accounted for.
  ASSERT_EQ(6, loads[1]); // Only the second chare is accounted for.
}

/**
 *  @brief The load of a PU is its background walltime if there are no fixed chares and its speed is 1.
 */
TEST_F(WorkloadFullyAwareTest, pu_workload_is_its_background_walltime) {
  std::vector<PU> pus {PU(true, 1, 1), PU(true, 1, 2)};
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 0)};
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(pus[i].bg_walltime, loads[i]);
}

/**
 *  @brief The load of a PU is its background walltime times its speed if there are no fixed chares.
 */
TEST_F(WorkloadFullyAwareTest, pu_workload_is_normalized_by_its_speed) {
  std::vector<PU> pus {PU(true, 1, 2), PU(true, 2, 2)};
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 0)};
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(pus[i].bg_walltime * pus[i].pe_speed, loads[i]);
}

/**
 *  @brief The load of fixed chares accounts for the PU load when it contains these tasks.
 */
TEST_F(WorkloadFullyAwareTest, pu_workload_accounts_for_fixed_tasks) {
  std::vector<PU> pus {PU(true, 1, 2), PU(true, 2, 2)};
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(false, 2, 1)}; // Tasks are unmigratable with walltime load 2.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  // The expected load depends if Charm++ traits dictates that there ARE unmigratable tasks.
  auto expected_loads = [](auto pu, auto hosted_chare) {
    auto pu_load = pu.pe_speed * pu.bg_walltime;
    return pu_load + hosted_chare.wallTime * pu.pe_speed;
  };

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(expected_loads(pus[i], chares[i]), loads[i]);
}

/**
 *  @brief The load of fixed chares accounts for the PU load when it contains these tasks and the implementation is migratability aware.
 */
TEST_F(WorkloadMigratabilityAwareTest, pu_workload_accounts_for_fixed_tasks) {
  std::vector<PU> pus {PU(true, 1, 2), PU(true, 2, 2)};
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(false, 2, 1)}; // Tasks are unmigratable with walltime load 2.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  // The expected load depends if Charm++ traits dictates that there ARE unmigratable tasks.
  auto expected_loads = [](auto pu, auto hosted_chare) {
    auto pu_load = pu.pe_speed * pu.bg_walltime;
    return pu_load + hosted_chare.wallTime * pu.pe_speed;
  };

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(expected_loads(pus[i], chares[i]), loads[i]);
}

/**
 *  @brief The load of fixed chares does not accounts for the PU load if the implementation is migratability unaware.
 */
TEST_F(WorkloadAvailabilityAwareTest, pu_workload_does_not_accounts_for_fixed_tasks) {
  std::vector<PU> pus {PU(true, 1, 2), PU(true, 2, 2)};
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(false, 2, 1)}; // Tasks are unmigratable with walltime load 2.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  // The expected load depends if Charm++ traits dictates that there ARE unmigratable tasks.
  auto expected_loads = [](auto pu, auto hosted_chare) { return pu.pe_speed * pu.bg_walltime; };

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(expected_loads(pus[i], chares[i]), loads[i]);
}

/**
 *  @brief The load of fixed chares does not accounts for the PU load if the implementation is fully unaware.
 */
TEST_F(WorkloadFullyUnawareTest, pu_workload_does_not_accounts_for_fixed_tasks) {
  std::vector<PU> pus {PU(true, 1, 2), PU(true, 2, 2)};
  std::vector<Chare> chares {Chare(false, 2, 0), Chare(false, 2, 1)}; // Tasks are unmigratable with walltime load 2.
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();

  // The expected load depends if Charm++ traits dictates that there ARE unmigratable tasks.
  auto expected_loads = [](auto pu, auto hosted_chare) { return pu.pe_speed * pu.bg_walltime; };

  for(unsigned i = 0; i < pus.size(); ++i)
    EXPECT_EQ(expected_loads(pus[i], chares[i]), loads[i]);
}

/**
 *  @brief The load of unavailable pus will not be computed for unavailable PUs.
 */
TEST_F(WorkloadFullyAwareTest, pu_workload_might_not_consider_unavailable_pus) {
  std::vector<PU> pus {PU(false, 1, 2), PU(true, 2, 2)}; // First PU is unavailable.
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 1)};
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();
  auto expected_loads = [](auto pu) { return pu.pe_speed * pu.bg_walltime; };

  ASSERT_EQ(1, loads.size());
  EXPECT_EQ(expected_loads(pus[1]), loads[0]);
}

/**
 *  @brief The load of unavailable pus will not be computed for unavailable PUs if the implementation is availability aware.
 */
TEST_F(WorkloadAvailabilityAwareTest, pu_workload_might_not_consider_unavailable_pus) {
  std::vector<PU> pus {PU(false, 1, 2), PU(true, 2, 2)}; // First PU is unavailable.
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 1)};
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();
  auto expected_loads = [](auto pu) { return pu.pe_speed * pu.bg_walltime; };

  ASSERT_EQ(1, loads.size());
  EXPECT_EQ(expected_loads(pus[1]), loads[0]);
}

/**
 *  @brief The load of unavailable pus will not be computed for unavailable PUs if the implementation is availability unaware.
 */
TEST_F(WorkloadMigratabilityAwareTest, pu_workload_might_not_consider_unavailable_pus) {
  std::vector<PU> pus {PU(false, 1, 2), PU(true, 2, 2)}; // First PU is unavailable.
  std::vector<Chare> chares {Chare(true, 2, 0), Chare(true, 2, 1)};
  
  set_pus(pus);
  set_chares(chares);

  auto loads = predict_pus_load();
  auto expected_loads = [](auto pu) { return pu.pe_speed * pu.bg_walltime; };

  ASSERT_EQ(2, loads.size());
  EXPECT_EQ(expected_loads(pus[0]), loads[0]);
  EXPECT_EQ(expected_loads(pus[1]), loads[1]);
}