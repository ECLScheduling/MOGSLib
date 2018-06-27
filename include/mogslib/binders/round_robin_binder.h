#pragma once

#include <schedulers/round_robin.h>

namespace MOGSLib {

/**
 * @brief This Bind specialization binds the concrete adapters T and P, required by the RounRobin scheduler, to their respective concepts, TaskData and PEData.
 */
template<typename T, typename P>
struct Bind<Scheduler::RoundRobin<T,P> > {
  static void bind(T* t, P *p) {
    Scheduler::RoundRobin<T,P>::TaskData::concrete = t;
    Scheduler::RoundRobin<T,P>::PEData::concrete = p;
  }
};

}