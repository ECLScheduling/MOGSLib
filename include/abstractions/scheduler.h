#pragma once

#include <string>

#include <system/type_definitions.h>
#include "bind.h"

namespace Abstraction {

/**
 * @brief A scheduler abstraction that unifies all template specializations together.
 */
class Scheduler {
public:

  const std::string name;

protected:
  Scheduler(std::string aname) : name(aname) {}

public:

  virtual ~Scheduler() {}

  /**
   * @brief The main method for a scheduler.
   * @details This method takes no parameters in order to offer simplicity to schedulers implementation in a way that the input must be setup outisde.
   */
  virtual TaskMap work() { 
    return nullptr; 
  };

};

/**
 * @brief A scheduler that makes nothing.
 */
class NoScheduler : public Scheduler {
public:

  NoScheduler() : Scheduler("nosched") {}
  virtual ~NoScheduler() {}
};

}