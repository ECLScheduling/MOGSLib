#pragma once

#include <schedulers/greedy.h>

#include <system/static.h>

BEGIN_NAMESPACE(Abstraction)

/**
 * @brief This Binder specialization binds the concrete adapters T and P, required by the Greedy scheduler, to their respective concepts, TaskData and PEData.
 */
template<typename T, typename P>
struct Binder<MOGSLib::Scheduler::Greedy<T,P> > {
  static void bind(T* t, P *p) {
    MOGSLib::Scheduler::Greedy<T,P>::TaskData::concrete = t;
    MOGSLib::Scheduler::Greedy<T,P>::PEData::concrete = p;
  }
};

END_NAMESPACE