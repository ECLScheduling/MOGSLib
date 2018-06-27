#pragma once

#include <schedulers/greedy.h>

namespace MOGSLib {

/**
 * @brief This Bind specialization binds the concrete adapters T and P, required by the Greedy scheduler, to their respective concepts, TaskData and PEData.
 */
template<typename T, typename P>
struct Bind<Scheduler::Greedy<T,P> > {
  static void bind(T* t, P *p) {
    Scheduler::Greedy<T,P>::TaskData::concrete = t;
    Scheduler::Greedy<T,P>::PEData::concrete = p;
  }
};

}