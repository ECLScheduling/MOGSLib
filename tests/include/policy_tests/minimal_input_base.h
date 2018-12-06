#pragma once

#include <type_definitions.h>

#include <inputs/minimal/default.h>

/**
 *  @class MinimalInputPolicyTests
 *  @brief A base class to test policies that use the minimal input.
 */
class MinimalInputPolicyTests : public ::testing::Test {
public:
  /// @brief Set the Input type to the default implementation of the minimal input type.
  using Input = MOGSLib::Input::Minimal<Index>;
  
  Schedule map;
  Input input;

  /**
   *  @brief Set the data about pu amount and task amount.
   *  @param p The amount of pus in the system.
   *  @param t The amount of tasks in the system.
   */
  void set_pus_and_tasks(const Index &p, const Index &t) {
    input.n_pus = p;
    input.n_tasks = t;
    map = Schedule(t);
  }

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    input = Input();
    map.clear();
  }
};