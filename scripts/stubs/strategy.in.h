#pragma once

#include <abstractions/scheduler.h>
#include <system/type_definitions.h>

namespace Scheduler {

@SCHED_DEPS@
class @SCHED_NAME@ : public Scheduler{
public:
  
  @SCHED_NAME@() : Scheduler("@SCHED_DISPLAY_NAME@") {}

  virtual TaskMap operator()() final {}

};

}