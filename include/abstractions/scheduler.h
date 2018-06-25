#pragma once

#include <string>
#include <system/type_definitions.h>

namespace Abstraction {

class Scheduler {
public:

  const std::string name;

  Scheduler(std::string aname) : name(aname) {}

  virtual ~Scheduler() {}

  virtual TaskMap operator()() = 0;
};

}