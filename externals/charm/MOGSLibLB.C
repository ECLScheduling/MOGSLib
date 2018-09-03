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
  std::string scheduler_name = "roundrobin";
  MOGSLib::RTS::Charm::stats = stats;

  auto map = MOGSLib::SchedulerCollection::schedule(scheduler_name);
  
  auto temporary_hack = std::get<0>(MOGSLib::SchedulerCollection::ConceptTuple::concepts);

  for(auto i = 0; i < temporary_hack.ntasks(); ++i)
    CkPrintf("Task %d in PE %d.\n",temporary_hack.task_ids[i], temporary_hack.PE_ids[map[i]]);

  delete map;
}


/*@}*/