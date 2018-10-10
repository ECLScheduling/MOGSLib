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
  std::string scheduler_name = "greedy";
  
  MOGSLib::RTS::Charm::stats = stats;
  auto map = MOGSLib::SchedulerCollection::schedule(scheduler_name);
  
  /*
   * This is a temporary hack to get the first concept in the collection of concepts.
   * As of now, when the library is compiled for Charm++, the first concept will always have the task data needed to migrate the tasks.
   * This will be revisited to be more readable and intuitive.
   */
  auto task_info = std::get<0>(MOGSLib::SchedulerCollection::ConceptTuple::concepts);

  //for(auto i = 0; i < task_info.ntasks(); ++i)
    //CkPrintf("Task %d in PE %d.\n",task_info.task_ids[i], task_info.PE_ids[map[i]]);

  for(auto i = 0; i < task_info.ntasks(); ++i)
    stats->assign(task_info.task_ids[i], task_info.PE_ids[map[i]]);

  delete map;
}


/*@}*/