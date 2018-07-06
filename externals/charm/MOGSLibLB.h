/**
 * \addtogroup CkLdb
*/
/*@{*/

#ifndef _MOGSLIBLB_H_
#define _MOGSLIBLB_H_

#include "CentralLB.h"
#include "MOGSLibLB.decl.h"

// #### MOGSLib Includes ####
#define LINKED_TO_CHARM

// MOGSLib RTS data
#include <mogslib/rts/charm.h>

// MOGSLib Scheduling Strategies
#include <schedulers/greedy.h>
#include <mogslib/binders/greedy_binder.h>

// MOGSLib Concrete Adapters
#include <mogslib/initializers/charm/basic_scheduler_input_init.h>

// #### End of MOGSLib Includes ####

#include <iostream>

#include "ckgraph.h"
#include <cassert>

void CreateMOGSLibLB();

class MOGSLibLB : public CBase_MOGSLibLB {
public:
  const static auto CharmEnumVal = MOGSLib::Abstraction::RuntimeSystemEnum::Charm;
  using CharmRTS = MOGSLib::Abstraction::RTS<CharmEnumVal>;

  template<typename T>
  using Initializer = MOGSLib::Abstraction::Initializer<CharmEnumVal, T>;

  template<typename T>
  using Binder = MOGSLib::Abstraction::Binder<T>;

  MOGSLibLB(const CkLBOptions &);
  MOGSLibLB(CkMigrateMessage *m): CBase_MOGSLibLB(m) {}
private:
  bool QueryBalanceNow(int step);
  void work(LDStats* stats);
};

#endif /* _MOGSLIBLB_H_ */

/*@}*/
