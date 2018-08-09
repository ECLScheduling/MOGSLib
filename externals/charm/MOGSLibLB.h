/**
 * \addtogroup CkLdb
*/
/*@{*/

#ifndef _MOGSLIBLB_H_
#define _MOGSLIBLB_H_

#include "CentralLB.h"
#include "MOGSLibLB.decl.h"

#include <iostream>

#include "ckgraph.h"
#include <cassert>

#include <mogslib/mogslib.h>

void CreateMOGSLibLB();

class MOGSLibLB : public CBase_MOGSLibLB {
public:

  MOGSLibLB(const CkLBOptions &);
  MOGSLibLB(CkMigrateMessage *m): CBase_MOGSLibLB(m) {}
private:
  bool QueryBalanceNow(int step);
  void work(LDStats* stats);
};

#endif /* _MOGSLIBLB_H_ */

/*@}*/
