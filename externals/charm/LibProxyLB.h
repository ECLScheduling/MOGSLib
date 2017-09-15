/**
 * \addtogroup CkLdb
*/
/*@{*/

#ifndef _LIBPROXYLB_H_
#define _LIBPROXYLB_H_

#include "CentralLB.h"
#include "LibProxyLB.decl.h"

#include <system/definitions.h>
#include <strategies/impl/greedy/greedyStrategy.h>
#include <strategies/input/charm/charmAdaptor.h>

#include "ckgraph.h"
#include <cassert>

void CreateLibProxyLB();

class LibProxyLB : public CBase_LibProxyLB {
public:
  using LibGreedyStrategy = GreedyStrategy<CharmAdaptor>;
  using LibOutput = typename LibGreedyStrategy::Output;

  CharmAdaptor *charmAdaptor;

  LibProxyLB(const CkLBOptions &);
  LibProxyLB(CkMigrateMessage *m):CBase_LibProxyLB(m) {}
private:
  bool QueryBalanceNow(int step);
  void work(LDStats* stats);
};

#endif /* _LibProxyLB_H_ */

/*@}*/
