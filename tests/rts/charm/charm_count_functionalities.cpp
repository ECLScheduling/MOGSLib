#include <gtest/gtest.h>

#include "mock/custom_traits.h"

#include <rts/charm/charm.h>
#include <rts/charm/charm.ipp>

/**
 *  @class CharmCountFunctionalitiesTest
 *  @brief Base test class for counting functionalities of the LBDB structure in Charm++
 *  @tparam AA Express if functionalities are aware of PUs availability.
 *  @tparam MA Express if functionalities are awawre of chares migratability.
 */
template<bool AA, bool MA>
class CharmCountFunctionalitiesTest {
public:
  using Traits = CustomCharmTraits<AA, MA>;
  using Charm = MOGSLib::RTS::Charm<Traits>;

  /// @brief Reference to a LDStats structure mock that contains a basic behavior close to the one expected by Charm RTS.
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
   *  @brief Sets the available tag of the first n PUs to true.
   *  @param n The amount of available PUs.
   *
   *  This function must be called after make_pus always.
   */
  void n_available_pus(const unsigned &n) {
    for(unsigned i = 0; i < n; ++i)
      stats->procs[i].available = true;
  }

  /**
   *  @brief Sets the amount of PUs, available and unavailable in the simulated platform.
   *  @param avail The amount of available PUs.
   *  @param unavail The amount of unavailable PUs.
   */
  void set_pus(const unsigned &avail, const unsigned &unavail = 0) {
    make_pus(avail+unavail);
    n_available_pus(avail);
  }

  /**
   *  @brief Allocate the chares in the stat structure.
   *  @param n The amount chares in the simulated application.
   */
  void make_chares(const unsigned &n) {
    stats->n_objs = n;
    stats->objData = std::make_unique<BaseLB::LDObjData[]>(n);
  }

  /**
   *  @brief Sets the migratable tag of chares to true.
   *  @param n The amount chares that will be migratable.
   *
   *  This implementation turns only the first n chares are going to be migratable.
   */
  void n_migratable_chares(const unsigned &n) {
    for(unsigned i = 0; i < n; ++i)
      stats->objData[i].migratable = true;
  }

  /**
   *  @brief Sets the amount of chares, migratable and unmigratable in the simulated application.
   *  @param avail The amount of migratable chares.
   *  @param unavail The amount of unmigratable chares.
   */
  void set_chares(const unsigned &mig, const unsigned &fixed = 0) {
    make_chares(mig+fixed);
    n_migratable_chares(mig);
  }
};

/**
 *  @class FullyAwareTest
 *  @brief Test class for counting functionalities of the LBDB structure in Charm++ that is aware of unmigratable chares and unavailable processors.
 */
class FullyAwareTest : public CharmCountFunctionalitiesTest<true,true>, public ::testing::Test {
  /// @brief SetUp should call its base class implementation.
  void SetUp() {  CharmCountFunctionalitiesTest<true,true>::SetUp();  }
};

/**
 *  @class FullyUnawareTest
 *  @brief Test class for counting functionalities of the LBDB structure in Charm++ that is not aware of unmigratable chares neither of unavailable processors.
 */
class FullyUnawareTest : public CharmCountFunctionalitiesTest<false,false>, public ::testing::Test {
  /// @brief SetUp should call its base class implementation.
  void SetUp() {  CharmCountFunctionalitiesTest<false,false>::SetUp();  }
};

/**
 *  @class AvailabilityAwareTest
 *  @brief Test class for counting functionalities of the LBDB structure in Charm++ that is unaware of unmigratable chares but aware of unavailable processors.
 */
class AvailabilityAwareTest : public CharmCountFunctionalitiesTest<true,false>, public ::testing::Test {
  /// @brief SetUp should call its base class implementation.
  void SetUp() {  CharmCountFunctionalitiesTest<true,false>::SetUp();  }
};

/**
 *  @class MigratabilityAwareTest
 *  @brief Test class for counting functionalities of the LBDB structure in Charm++ that is aware of unmigratable chares but not of unavailable processors.
 */
class MigratabilityAwareTest : public CharmCountFunctionalitiesTest<false,true>, public ::testing::Test {
  /// @brief SetUp should call its base class implementation.
  void SetUp() {  CharmCountFunctionalitiesTest<false,true>::SetUp();  }
};

/**
 *  @brief Test if a registered PU is found by LBDB.
 */
TEST_F(FullyAwareTest, will_find_one_pu_if_it_is_available) {
  set_pus(1);

  ASSERT_EQ(1, Charm::LBDB::PU::count());
}

/**
 *  @brief Test if two registered PUs are found by LBDB.
 */
TEST_F(FullyAwareTest, will_find_two_pus_if_they_are_available) {
  set_pus(2);

  ASSERT_EQ(2, Charm::LBDB::PU::count());
}

/**
 *  @brief Test if a registered chare is found by LBDB.
 */
TEST_F(FullyAwareTest, will_find_one_chare_if_it_is_migratable) {
  set_chares(1);

  ASSERT_EQ(1, Charm::LBDB::Chare::count());
}

/**
 *  @brief Test if two registered chares are found by LBDB.
 */
TEST_F(FullyAwareTest, will_find_two_chares_if_they_are_migratable) {
  set_chares(2);

  ASSERT_EQ(2, Charm::LBDB::Chare::count());
}

/**
 * @brief Test if an unmigratable chare is disconsidered by a fully aware functionality implementation.
 */
TEST_F(FullyAwareTest, will_find_one_chare_if_it_is_the_only_migratable) {
  set_chares(1,1);
  ASSERT_EQ(1, Charm::LBDB::Chare::count());
}

/**
 * @brief Test if an unmigratable chare is disconsidered by a migratability aware functionality implementation.
 */
TEST_F(MigratabilityAwareTest, will_find_one_chare_if_it_is_the_only_migratable) {
  set_chares(1,1);
  ASSERT_EQ(1, Charm::LBDB::Chare::count());
}

/**
 * @brief Test if an unmigratable chare is considered by a migratability unaware functionality implementation.
 */
TEST_F(AvailabilityAwareTest, will_find_all_chares_regardless_of_migratability) {
  set_chares(1,1);
  ASSERT_EQ(2, Charm::LBDB::Chare::count());
}

/**
 * @brief Test if an unavailable processor is disconsidered by a fully aware implementation.
 */
TEST_F(FullyAwareTest, will_find_one_pu_if_it_is_the_only_available) {
  set_pus(1, 1);

  ASSERT_EQ(1, Charm::LBDB::PU::count());
}

/**
 * @brief Test if an unavailable processor is disconsidered by a availability aware implementation.
 */
TEST_F(AvailabilityAwareTest, will_find_one_pu_if_it_is_the_only_available) {
  set_pus(1, 1);

  ASSERT_EQ(1, Charm::LBDB::PU::count());
}

/**
 * @brief Test if an unavailable processor is considered by a availability unaware implementation.
 */
TEST_F(MigratabilityAwareTest, will_find_one_pu_if_it_is_the_only_available) {
  set_pus(1, 1);

  ASSERT_EQ(2, Charm::LBDB::PU::count());
}

/**
 * @brief Test if an unavailable processor is considered by a fully unaware implementation.
 */
TEST_F(FullyUnawareTest, will_find_one_pu_if_it_is_the_only_available) {
  set_pus(1, 1);

  ASSERT_EQ(2, Charm::LBDB::PU::count());
}