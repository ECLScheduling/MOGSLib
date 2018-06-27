#pragma once

#include <string>

#include <system/type_definitions.h>
#include "bind.h"

namespace Abstraction {

class Scheduler {
public:

  const std::string name;

protected:
  Scheduler(std::string aname) : name(aname) {}

public:

  virtual ~Scheduler() {}

  virtual TaskMap work() { 
    return nullptr; 
  };

};

class NoScheduler : public Scheduler {
public:

  NoScheduler() : Scheduler("nosched") {}
  virtual ~NoScheduler() {}
};

}