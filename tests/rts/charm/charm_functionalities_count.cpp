#include <gtest/gtest.h>

#include "mock/LDStats.h"

#include <rts/charm/charm.h>
#include <rts/charm/charm.ipp>

using Charm = MOGSLib::Abstraction::RTS<MOGSLib::RuntimeSystemEnum::Charm>;

class CharmFunctionalitiesTest : public ::testing::Test {
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

  void n_available_pus(const unsigned &n) {
    for(unsigned i = 0; i < n; ++i)
      stats->procs[i].available = true;
  }

  void set_pus(const unsigned &avail, const unsigned &unavail = 0) {
    make_pus(avail+unavail);
    n_available_pus(avail);
  }

  void make_chares(const unsigned &n) {
    stats->n_objs = n;
    stats->objData = std::make_unique<BaseLB::LDObjData[]>(n);
  }

  void n_migratable_chares(const unsigned &n) {
    for(unsigned i = 0; i < n; ++i)
      stats->objData[i].migratable = true;
  }

  void set_chares(const unsigned &mig, const unsigned &fixed = 0) {
    make_chares(mig+fixed);
    n_migratable_chares(mig);
  }

};

// Checking the amounts of PUs in the system.
TEST_F(CharmFunctionalitiesTest, will_find_one_pu_if_it_is_available) {
  set_pus(1);

  ASSERT_EQ(1, Charm::LBDB::PU::count());
}

TEST_F(CharmFunctionalitiesTest, will_find_two_pus_if_they_are_available) {
  set_pus(2);

  ASSERT_EQ(2, Charm::LBDB::PU::count());
}

/**
 * @details This test must have the Charm++ traits changed to have both behaviors tested.
 */
TEST_F(CharmFunctionalitiesTest, will_find_one_pu_if_it_is_the_only_available) {
  set_pus(1, 1);

  decltype(Charm::LBDB::PU::count()) expected = (Charm::Traits::check_for_unavailable_pus)? 1 : 2;

  ASSERT_EQ(expected, Charm::LBDB::PU::count());
}

// Checking the amounts of chares in the system.

TEST_F(CharmFunctionalitiesTest, will_find_one_chare_if_it_is_migratable) {
  set_chares(1);

  ASSERT_EQ(1, Charm::LBDB::Chare::count());
}

TEST_F(CharmFunctionalitiesTest, will_find_two_chares_if_they_are_migratable) {
  set_chares(2);

  ASSERT_EQ(2, Charm::LBDB::Chare::count());
}

/**
 * @details This test must have the Charm++ traits changed to have both behaviors tested.
 */
TEST_F(CharmFunctionalitiesTest, will_find_one_chare_if_it_is_the_only_migratable) {
  set_chares(1,1);

  decltype(Charm::LBDB::PU::count()) expected = (Charm::Traits::check_for_fixed_chares)? 1 : 2;

  ASSERT_EQ(expected, Charm::LBDB::Chare::count());
}