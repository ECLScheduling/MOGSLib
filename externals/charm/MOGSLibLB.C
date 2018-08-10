/**
 * \addtogroup CkLdb
*/
/*@{*/

#include "MOGSLibLB.h"

CreateLBFunc_Def(MOGSLibLB, "A strategy that calls MOGSLib to execute its chosen global scheduler.")

#include "MOGSLibLB.def.h"

MOGSLibLB::MOGSLibLB(const CkLBOptions &opt): CBase_MOGSLibLB(opt)
{
  lbname = (char*)"MOGSLibLB";
  if (CkMyPe() == 0)
    CkPrintf("[%d] MOGSLibLB created\n",CkMyPe());
}

bool MOGSLibLB::QueryBalanceNow(int _step)
{
  return true;
}

void MOGSLibLB::work(LDStats* stats) {
  MOGSLib::Definitions::RTS::stats = stats;

  // Declare scheduler
  MOGSLib::Definitions::Scheduler scheduler;

  // Declare and instantiate concrete adapters
  auto adapter0 = new MOGSLib::Definitions::Adapter0();

  // Initialize concrete adapters
  MOGSLib::Definitions::Initializer<MOGSLib::Definitions::Adapter0>::init(adapter0);

  // Bind concrete adapters to concepts.
  MOGSLib::Definitions::Binder::bind(adapter0, adapter0);

  auto map = scheduler.work();
  for(auto i = 0; i < adapter0->ntasks(); ++i)
    CkPrintf("Task %d in PE %d.\n",adapter0->task_ids[i], adapter0->PE_ids[map[i]]);

  delete adapter0;
}


/*@}*/