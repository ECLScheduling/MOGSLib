#include <gtest/gtest.h>

#include <iostream>
#include <autogen/schedulers.h>

#define LINKED_TO_CHARM
namespace BaseLB {
  struct LDStats {};
}

#include <mogslib/rts/charm.h>

class TestingRandomStuff : public ::testing::Test {

};

// TEST_F(TestingRandomStuff, option_test) {
//   auto sched = MOGSLib::Schedulers::get_by_name("roundrobin");

//   if(sched->has){
//     auto schedptr = MOGSLib::Optional::get_value<MOGSLib::Schedulers::SchedulerPtr>(sched);
//     std::cout << schedptr->name << std::endl;
//     //schedptr->work();
//   }
// }

TEST_F(TestingRandomStuff, charm_link) {
  MOGSLib::RTS::Charm::stats = new BaseLB::LDStats();
}
