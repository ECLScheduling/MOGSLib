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
  //TODO: lacking the creation of concepts.
  auto map = MOGSLib::SchedulerCollection::schedule("greedy");
  
  for(auto i = 0; i < adapter0->ntasks(); ++i)
    CkPrintf("Task %d in PE %d.\n",adapter0->task_ids[i], adapter0->PE_ids[map[i]]);

  delete map;
}


/*@}*/