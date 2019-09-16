#pragma once

#define Ctx(N) Context::N
#define CtxTuple(I) typename std::tuple_element<I, Contexts>::type

#define Sched(N, I) Scheduler::N<CtxTuple(I)>
  