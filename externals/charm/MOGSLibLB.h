/**
 * \addtogroup CkLdb
*/
/*@{*/

#ifndef _MOGSLIBLB_H_
#define _MOGSLIBLB_H_

#include "CentralLB.h"
#include "MOGSLibLB.decl.h"

#include <system/traits.h>
#include <strategies/binLPT/binLPT.h>
#include <adaptors/charm/charmAdaptorWithGenericStructure.h>

#include "ckgraph.h"
#include <cassert>

void CreateMOGSLibLB();

class MOGSLibLB : public CBase_MOGSLibLB {
public:
  using UInt = Traits<DefaultTypes>::UInt;
  using Adaptor = CharmAdaptorWithGenericStructure<UInt>;
  using Strategy = BinLPT::Strategy<Adaptor>;
  using Output = typename Strategy::Output;

  Adaptor *adaptor;

  MOGSLibLB(const CkLBOptions &);
  MOGSLibLB(CkMigrateMessage *m): CBase_MOGSLibLB(m) {}
private:
  bool QueryBalanceNow(int step);
  void work(LDStats* stats);
};

#endif /* _MOGSLIBLB_H_ */

/*@}*/
