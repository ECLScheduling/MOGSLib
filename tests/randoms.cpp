#include <gtest/gtest.h>

#include <iostream>
#include <autogen/schedulers.h>

class TestingRandomStuff : public ::testing::Test {

};

TEST_F(TestingRandomStuff, option_test) {
  auto sched = MOGSLib::Schedulers::get_by_name("roundrobin");

  if(sched->has){
    auto schedptr = MOGSLib::Optional::get_value<MOGSLib::Schedulers::SchedulerPtr>(sched);
    std::cout << schedptr->name << std::endl;
    //schedptr->work();
  }
}