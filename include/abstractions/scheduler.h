#pragma once

#include <string>

#include <system/type_definitions.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief A scheduler abstraction that unifies all template specializations together.
 */
class Scheduler {
public:

  const std::string name;

protected:
  Scheduler(const std::string _name) : name(_name) {}

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

END_NAMESPACE