#pragma once

#include <system/traits.h>

#include <strategies/output/migrationElement.h>

#include <algorithm>
#include <set>
#include <queue>
#include <cmath>

struct MigrationElementDescriptionAnalyzer {
  typedef Traits<MigrationElement>::Load Load;

  struct Result {
    Load min;
    Load max;
    double mean = 0;

    Load q1 = 0;
    Load median = 0;
    Load q3 = 0;

    double standardDeviation = 0;
  };


  static Result analyze(MigrationElement *output) {
    Result result;
    Load loadSum = 0;

    double *variance;
    double varianceSum = 0;
    int i = 0;

    // ################ Sanity Check ################
    if(output->mappedPEs.size() == 0) {
      return result;
    }
    // ##############################################

    variance = new double[output->mappedPEs.size()];

    result.min = output->mappedPEs[0]->load();
    result.max = output->mappedPEs[0]->load();

    std::vector<Load> sortedLoads;

    // ########### Min/Max/Mean #####################
    for(auto PE : output->mappedPEs) {
      Load PELoad = PE->load();

      // Ordering for median
      sortedLoads.push_back(PELoad);
      
      // Mean calculation
      loadSum += PELoad;

      // Min calculation
      if(PELoad < result.min) {
        result.min = PELoad;
      }

      // Max calculation
      if(PELoad > result.max) {
        result.max = PELoad;
      }

      // Variance calculation
      variance[i] = PELoad;
      ++i;
    }

    result.mean = loadSum/output->mappedPEs.size();
    // ##############################################

    // ############### Standard Deviation ###########
    for(int j = 0; j < i; ++j) {
      double temp = variance[j] - result.mean;
      variance[j] = temp * temp;
      varianceSum += variance[j];
    }

    varianceSum /= i;

    result.standardDeviation = std::sqrt(varianceSum);
    // ##############################################

    // ############## Median ########################
    std::make_heap(sortedLoads.begin(), sortedLoads.end()); // applying heap-sort Greater to lesser

    result.q3 = sortedLoads[i/4]; // Inverted because of sortdLoads is descending ordering.
    result.median = sortedLoads[(i-1)/2];
    result.q1 = sortedLoads[i*3/4]; // Inverted because of sortdLoads is descending ordering.

    return result;
  }

};