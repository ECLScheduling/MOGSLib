#pragma once

#include <concepts/scheduler/scheduler.h>

#include "defaults.h"

#include <vector>
#include <algorithm>

namespace Greedy {

/**
 * @brief This class encapsulates the implementation of a Greedy load balancer strategy.
 */
template <typename Input = Defaults::Input>
class Scheduler : public Concepts::Scheduler<Input> {
public:

  using Output = typename Concepts::Scheduler<Input>::Output;
  using Index = typename Traits<SchedulerInput>::Index;
  using Load = typename Traits<SchedulerInput>::Load;

  virtual ~Scheduler() {}

protected:

  struct LoadBearer {
    Load load;
    Index id;

    void operator =(const LoadBearer &t) {
      load = t.load;
      id = t.id;
    }

    bool operator >(const LoadBearer &t) const {
      return load > t.load;
    }

    bool operator <(const LoadBearer &t) const {
      return load < t.load;
    }
  };

  static inline bool maxCmp(const LoadBearer& a, const LoadBearer& b) {
    return a < b;
  }

  static inline bool minCmp(const LoadBearer& a, const LoadBearer& b) {
    return a > b;
  }

  /**
   * @brief The strategy specific code for every strategy implementation. This method must be implemented for each strategy and inside it's code it must modify the lbOutput variable.
   */
  virtual Output map(Input &input);

};

#include "scheduler.ipp"

}