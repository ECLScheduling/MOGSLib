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
  MOGSLib::Strategy strategy;
  #ifdef USE_STRUCTURE_K
  MOGSLib::UInt k = 5;
  #endif

  CkPrintf("At Load Balancer...\n");
  
  adaptor = new MOGSLib::Adaptor(stats);
  #ifdef USE_STRUCTURE_K
  adaptor->setStructure(k);
  #endif
  
  CkPrintf("Adaptor Initialized... Invoking library implementation...\n");

  auto output = strategy.mapTasks(adaptor);
  
  CkPrintf("Applying library mapping...\n");

  for(UInt i = 0; i < adaptor->ntasks(); ++i)
    stats->assign(i, output[i]);

  delete adaptor;
}


/*@}*/
