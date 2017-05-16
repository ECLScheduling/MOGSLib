#ifndef __LBOUTPUT_H__
#define __LBOUTPUT_H__

#include <system/traits.h>

/**
 * Class that serve as an abstraction of the Load balancer's output.
 */
class LBOutput {
public:
  typedef Traits<LBOutput>::ProcessingElement ProcessingElement;
  typedef Traits<LBOutput>::Task Task;
  typedef Traits<LBOutput>::TaskMap TaskMap;

  const TaskMap taskMap;

  LBOutput(const TaskMap &mappings) : taskMap(mappings) {}
  virtual ~LBOutput() {}
};

#endif