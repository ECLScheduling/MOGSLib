/**
 * \addtogroup CkLdb
*/
/*@{*/

#include "MOGSLibLB.h"

CreateLBFunc_Def(MOGSLibLB, "A strategy that calls MOGSLib to execute its chosen global scheduler.")

#include "MOGSLibLB.def.h"
#include <mogslib/mogslib.ipp>

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

  std::string strategy = "greedy"; // Change here to select a strategy to call in MOGSLib.
  CkPrintf("MOGSLibLB calling %s scheduler\n", strategy);
  auto map = MOGSLib::API::work(strategy);
  CkPrintf("MOGSLibLB decided Mapping\n");

  // Code to assign the mapping from MOGSLib to the Charm++ centralized loadbalancing API
  auto &chare_ids = MOGSLib::RTS::Charm::chare_ids;
  auto &pu_ids = MOGSLib::RTS::Charm::pu_ids;

  MOGSLib::RTS::Charm::Id i = 0;
  for(auto chare : chare_ids)
    stats->assign(chare, pu_ids[map[i++]]);
  // ----------------------------------------------------------
}


/*@}*/