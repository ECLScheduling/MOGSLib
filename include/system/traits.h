#ifndef __TRAITS_LB_H__
#define __TRAITS_LB_H__

#include <system/types.h>
#include <map>
#include <unordered_set>

template<typename T>
struct Traits {};

template<>
struct Traits<LBOutput> {
  typedef int ProcessingElement;
  typedef int Task;
  typedef std::unordered_set<Task> TaskSet;

  typedef std::map<ProcessingElement,TaskSet> TaskMap;
  typedef std::pair<ProcessingElement,TaskSet> MapPair;
};

template<>
struct Traits<BasicInput> {
  typedef unsigned int Load;
};

#endif