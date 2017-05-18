#pragma once

#include <lb/loadBalancer.h>

class GreedyLB : public LoadBalancer<BasicInput> {
public:

  //TODO: This is just a temporary implementation to exemplify a LB's implementation.
  const MigrationElement& work(const std::weak_ptr<const BasicInput> input) const { return lbOutput; }
};

