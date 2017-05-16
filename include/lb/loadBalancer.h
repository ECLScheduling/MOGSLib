#ifndef __LOAD_BALANCER_H__
#define __LOAD_BALANCER_H__

#include <lb/lbOutput.h>
#include <memory>

/**
 * Class from which every load balancer must inherit from. The Load balancer's input class must be provided at compile time.
 */
template<typename LBInput>
class LoadBalancer {

public:

  /**
   * The main entrypoint for every load balancer.
   * @param input The LB's relevant input about the environment, architecture and tasks.
   * @return The result task mapping given by the load balancer.
   */
  virtual const LBOutput& work(const std::weak_ptr<const LBInput> input) const = 0;
};

#endif