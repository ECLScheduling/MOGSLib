#ifndef __TRAITS_LB_H__
#define __TRAITS_LB_H__

#include <system/types.h>
#include <map>

template<typename T>
struct Traits {};

template<>
struct Traits<LBOutput> {
  typedef int ProcessingElement;
  typedef int Task;

  typedef std::map<Task,ProcessingElement> TaskMap;
};

template<>
struct Traits<BasicInput> {
  typedef unsigned int Load;
};

#endif