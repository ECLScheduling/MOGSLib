#pragma once

#include <algorithm>
#include <set>

template <typename Unit>
struct DescriptiveAnalyzer {

  struct Result {
    Unit min;
    Unit max;
    double mean;
    Unit median;
    double standardDeviation;
  };


  Result analyze(Unit load[], unsigned int size) {
    assert(size > 0);
    Result result;

    result.sum = 0;
    for(unsigned int i = 0; i < size; ++i) {
      orderedSet.insert(load[i]);
      result.sum += load[i];
    }

    result.sum /= size;
    result.min = *(orderedSet.start());
    result.max = *(orderedSet.end());
  }

  Unit mean(Unit *load, unsigned int size) {
    assert(size > 0);

    Unit sum = load[0];

    for(unsigned int i = 1; i < size; ++i) {
      sum += load[i];
    }

    return sum/size;
  }

};