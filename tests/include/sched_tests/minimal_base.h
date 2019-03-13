#pragma once

#include <type_definitions.h>

#include "ctx_base.h"

class BaseSchedulerTests : public ::testing::Test {
public:
  using Context = MOGSLib::Context::Base<Id>;
  using Schedule = std::vector<typename Context::Id>;
  Schedule map;

  void tasks(const Id &n) {
    Context::_input.tasks = n;
  }

  void pus(const Id &n) {
    Context::_input.pus = n;
  }

  virtual Schedule call_scheduler() = 0;

  void execute_scheduler() {
    map = std::move(call_scheduler());
  }

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    Context::_input.tasks = 0;
    Context::_input.pus = 0;
  }
};