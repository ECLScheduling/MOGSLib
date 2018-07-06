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
  // MOGSLib::Strategy strategy;
  // #ifdef USE_STRUCTURE_K
  // MOGSLib::UInt k = 5;
  // #endif
  
  // adaptor = new MOGSLib::Adaptor(stats);
  // #ifdef USE_STRUCTURE_K
  // adaptor->setStructure(k);
  // #endif

  // BEGIN NOVAS COISAS
  
  // Map system-specific structures.
  CharmRTS::stats = stats;
  
  // Declare scheduler
  using ConcreteAdapter = MOGSLib::Adapter::BasicSchedulerInput;
  using Scheduler = MOGSLib::Scheduler::Greedy<ConcreteAdapter>;

  Scheduler scheduler;

  // Declare and instantiate concrete adapters
  auto basic_input = new ConcreteAdapter();

  // Initialize concrete adapters
  Initializer<ConcreteAdapter>::init(basic_input);

  // Bind concrete adapters to concepts.
  Binder<Scheduler>::bind(basic_input, basic_input);

  // Call Scheduler with specific concepts.
  auto map = scheduler.work();
  for(auto i = 0; i < basic_input->ntasks(); ++i)
    CkPrintf("Task %d in PE %d.\n",basic_input->task_ids[i], basic_input->PE_ids[map[i]]);

  // END NOVAS COISAS

  // std::string scheduler_name = "greedy";
  // auto scheduler_opt = MOGSLib::Schedulers::get_by_name(scheduler_name);
  // if(scheduler_opt->has) {
  //  // Update all the dependencies
  //  auto scheduler_ptr = Optional::get_value<MOGSLib::Schedulers::SchedulerPtr>(scheduler_opt);
  //  auto map = scheduler_ptr->work();
  // // Assign output
  // } else {
  // // Scheduler name is invalid
  // }

  // auto output = strategy.mapTasks(adaptor);
  
  // for(UInt i = 0; i < adaptor->ntasks(); ++i)
  //   stats->assign(adaptor->task_ids[i], adaptor->pe_ids[output[i]]);

  // delete adaptor;
}


/*@}*/
