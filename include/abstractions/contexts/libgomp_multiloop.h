#pragma once

#include "libgomp.h"
#include <model/policies/dependencies/base.h>

namespace MOGSLib { namespace Context {

/**
 * @class LibGOMPMultiloop
 * @brief An extension for the LibGOMP context where the schedules can be kept for future use.
 */
struct LibGOMPMultiloop : public LibGOMP{
public:
  using Schedule = typename MOGSLib::Dependency::Base<Id>::Schedule;

protected:
  unsigned current_loop;
  bool overwrite;
  std::vector<Schedule> schedules;

public:

  inline Id* scheduleRaw() {
    return schedules[current_loop].data();
  }

  /**
   * @brief Set the loop id for the next OpenMP loop.
   * @param id The id for the next loop.
   * @return The internal registered id for the loop.
   * @details This method returns id if the loop was already registered. If no loop indexed by id is found, this method returns the id for the new loop.
   */
  unsigned set_loop(const unsigned &id) {
    current_loop = (id >= schedules.size())? schedules.size() : id;
    return current_loop;
  }

  /**
   * @brief Decides if the next schedule decision should overwrite the previous one.
   */
  void set_overwrite(const bool &b) {
    overwrite = b;
  }

  /**
   * @brief Checks if there is a previous schedule for the current loop id.
   */
  bool has_schedule() const {
    return current_loop < schedules.size();
  }

  /**
   * @brief Evaluates if the next schedule decision should be recalculated.
   */
  virtual bool recalculate() const {
    return !has_schedule() || overwrite;
  }

  /**
   * @brief Returns the current schedule decision associated with the current loop id.
   */
  inline Schedule& schedule() {
    if(!has_schedule())
      schedules.push_back(Schedule());
    schedules[current_loop].resize(_input.ntasks());
    return schedules[current_loop];
  }

};

}}