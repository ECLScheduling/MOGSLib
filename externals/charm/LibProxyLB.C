/**
 * \addtogroup CkLdb
*/
/*@{*/

#include "LibProxyLB.h"

CreateLBFunc_Def(LibProxyLB, "Dummy load balancer, like a normal one but with empty strategy")

#include "LibProxyLB.def.h"

LibProxyLB::LibProxyLB(const CkLBOptions &opt): CBase_LibProxyLB(opt)
{
  lbname = (char*)"LibProxyLB";
  if (CkMyPe() == 0)
    CkPrintf("[%d] LibProxyLB created\n",CkMyPe());
}

bool LibProxyLB::QueryBalanceNow(int _step)
{
  return true;
}

void LibProxyLB::work(LDStats* stats) {
  LibGreedyStrategy strategyImpl;

  CkPrintf("At Load Balancer...\n");
  charmAdaptor = new CharmAdaptor(stats);
  CkPrintf("Adaptor Initialized... Invoking library implementation...\n");

  auto output = strategyImpl.mapTasks(*charmAdaptor);
  CkPrintf("Applying library mapping...\n");

  auto map = output.map;
  for(auto it= map.begin(); it!= map.end(); ++it) {
    auto PEId = it->first;
    for(auto taskId : it->second)
      stats->assign(taskId, PEId);
  }

  delete charmAdaptor;
}


/*@}*/
