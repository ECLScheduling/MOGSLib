#include <gtest/gtest.h>

#include <iostream>

#include <tuple>

class TestingRandomStuff : public ::testing::Test {

};

TEST_F(TestingRandomStuff, tuple_size) {
  std::tuple<int,int> t;
  std::cout << sizeof t << std::endl;
  std::cout << sizeof(int) << std::endl;
}

// // TEST_F(TestingRandomStuff, option_test) {
// //   auto sched = MOGSLib::Schedulers::get_by_name("roundrobin");

// //   if(sched->has){
// //     auto schedptr = MOGSLib::Optional::get_value<MOGSLib::Schedulers::SchedulerPtr>(sched);
// //     std::cout << schedptr->name << std::endl;
// //     //schedptr->work();
// //   }
// // }

// TEST_F(TestingRandomStuff, charm_link) {
//   MOGSLib::RTS::Charm::stats = new BaseLB::LDStats();
// }
