#pragma once

#include <type_definitions.h>

#include "ctx_base.h"

class BaseSchedulerTests : public ::testing::Test {
public:
  using Context = MOGSLib::Context::Base<Id>;
  using Schedule = std::vector<typename Context::Id>;

  Context ctx;
  Schedule map;

  void tasks(const Id &n) {
    ctx._input.tasks = n;
  }

  void pus(const Id &n) {
    ctx._input.pus = n;
  }

  virtual Schedule call_scheduler(Context &c) = 0;

  void execute_scheduler() {
    map = std::move(call_scheduler(ctx));
  }

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    ctx._input.tasks = 0;
    ctx._input.pus = 0;
  }
};