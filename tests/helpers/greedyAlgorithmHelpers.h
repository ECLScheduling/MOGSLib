#pragma once
#include "test_traits.h"

namespace GreedyAlgorithmHelper {

  /**
   * Simplest type possible to mock a PE in terms of validating the Greedy Algorithm logic.
   */
  struct DummyPE {
    typedef TestTraits<GreedyAlgorithmTest>::DummyTask DummyTask;

    std::vector<DummyTask> vector;

    void mapTask(DummyTask i) { 
      vector.push_back(i);
    }

    const DummyTask sum() const {
      DummyTask retval = 0;
      for(DummyTask n : vector)
        retval += n;
      return retval;
    }

    bool operator>(const DummyPE &o) const {
      return sum() > o.sum();
    }

  };

}