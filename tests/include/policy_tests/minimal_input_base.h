#pragma once

#include <type_definitions.h>

#include <model/policies/dependencies/base.h>
#include <abstractions/structures/input/base.h>

using Deps = MOGSLib::Dependency::Base<Id>;
using Schedule = typename Deps::Schedule;

/**
 *  @class MinimalInputPolicyTests
 *  @brief A base class to test policies that use the minimal input.
 */
class MinimalInputPolicyTests : public ::testing::Test {
public:
  /// @brief Set the Input type to the default implementation of the minimal input type.
  using Input = MOGSLib::Input::Base<Id>;
  
  Schedule map;
  Input input;

  /**
   *  @brief Set the data about pu amount and task amount.
   *  @param p The amount of pus in the system.
   *  @param t The amount of tasks in the system.
   */
  void set_pus_and_tasks(const Id &p, const Id &t) {
    input.pus = p;
    input.tasks = t;
    map = Schedule(t);
  }

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    input = Input();
    map.clear();
  }
};