#ifndef __GREEDY_LB_H__
#define __GREEDY_LB_H__

#include <lb/loadBalancer.h>

class GreedyLB : public LoadBalancer<BasicInput> {
public:

  //TODO: This is just a temporary implementation to exemplify a LB's implementation.
  const LBOutput& work(const std::weak_ptr<const BasicInput> input) const { return LBOutput(LBOutput::TaskMap()); }
};

#endif