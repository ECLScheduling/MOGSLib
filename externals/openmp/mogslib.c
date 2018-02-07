#include <system/definitions.h>

#ifdef RTS_IS_OPENMP

#include <adaptors/openmp/openMPDefaultAdaptor.h>
#include <strategies/binLPT/binLPT.h>
#include <mogslib.h>

#define INPUT_DEF OpenMPDefaultAdaptor
#define STRATEGY_DEF BinLPT::Strategy<INPUT_DEF>

using Input = INPUT_DEF;
using Strategy = STRATEGY_DEF;

void call_pe_count(void *obj, unsigned npe) {
  static_cast<INPUT_DEF *>(obj)->setPECount(npe);
}

void call_strategy_map(void *obj, void *arg) {
  static_cast<STRATEGY_DEF *>(obj)->mapTasks(*static_cast<INPUT_DEF *>(arg));
}

extern "C" {

void input_set_PE_count(void* input, unsigned npe) {
  call_pe_count(input, npe);
}

void strategy_map_tasks(void* strategy, void* input) {
  call_strategy_map(strategy, input);
}

}

#endif // RTS_IS_OPENMP