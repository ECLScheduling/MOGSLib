#pragma once

#include <type_definitions.h>

#include "ctx_workload_aware.h"

#include <load_generator.h>

class WorkloadSchedulerTests : public ::testing::Test {
public:
  /// @brief Set the LoadGenerator type to the default load generator.
  using LoadGenerator = UnitTest::LoadGenerator<>;
  using Context = MOGSLib::Context::WorkloadAware<Id, Load>;
  using Schedule = std::vector<typename Context::Id>;

  Schedule map;

  void tasks(const Id &n) {
    Context::_input.tasks.resize(n);
  }

  void pus(const Id &n) {
    Context::_input.pus.resize(n);
  }

  void k(const Id &n) {
    Context::_k = n;
  }

  Load& pu_at(const Id &n) {
    return Context::_input.pus[n];
  }

  Load& task_at(const Id &n) {
    return Context::_input.tasks[n];
  }

  virtual Schedule call_scheduler() = 0;

  void execute_scheduler() {
    map = std::move(call_scheduler());
  }

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    Context::_input.tasks.clear();
    Context::_input.pus.clear();
  }

  /**
   *  @brief Set the workload of the tasks.
   *  @param gen A function to generate the load of a task given its index.
   */
  void task_loads(const Id &n, Load (*gen)(const Id &)) {
    tasks(n);
    Id i = 0;
    std::transform(Context::_input.tasks.begin(), Context::_input.tasks.end(), Context::_input.tasks.begin(), [&i, &gen](Load) { return gen(i++); });
  }

  /**
   *  @brief Set the workload of the PUs.
   *  @param gen A function to generate the load of a task given its index.
   */
  void pu_loads(const Id &n, Load (*gen)(const Id &)) {
    pus(n);
    Id i = 0;
    std::transform(Context::_input.pus.begin(), Context::_input.pus.end(), Context::_input.pus.begin(), [&i, &gen](Load) { return gen(i++); });
  }
};