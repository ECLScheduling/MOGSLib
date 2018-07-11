/**
 * \addtogroup CkLdb
*/
/*@{*/

#include "MOGSLibLB.h"

CreateLBFunc_Def(MOGSLibLB, "Dummy load balancer, like a normal one but with empty strategy")

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
  MOGSLib::RTS::Charm::stats = stats;

  auto map = MOGSLib::Schedulers::map("greedy");
  auto adapter = MOGSLib::Concept::TaskData<MOGSLib::Adapter::BasicSchedulerInput>::concrete;
  
  for(auto i = 0; i < adapter->ntasks(); ++i)
    CkPrintf("Task %d in PE %d.\n",adapter->task_ids[i], adapter->PE_ids[map[i]]);
  
  //TODO: Free the memory
}


/*@}*/