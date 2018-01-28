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
  Strategy strategy;
  UInt k = 5;

  CkPrintf("At Load Balancer...\n");
  
  adaptor = new Adaptor(stats);
  adaptor->setStructure(k);
  
  CkPrintf("Adaptor Initialized... Invoking library implementation...\n");

  auto output = strategy.mapTasks(*adaptor);
  
  CkPrintf("Applying library mapping...\n");

  auto map = output.map;
  for(auto it= map.begin(); it!= map.end(); ++it) {
    auto PEId = it->first;
    for(auto taskId : it->second)
      stats->assign(taskId, PEId);
  }

  delete adaptor;
}


/*@}*/
