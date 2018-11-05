#include <iostream>
#include <mogslib/mogslib.h>

using Load = MOGSLib::Load;
using Index = MOGSLib::Index;

/**
 * This data block is composed of data that the RTS can perceive
 * The namespace is not necessary.
 **/
namespace LoadBalancingData {
  Index ntasks = 8; // Charm++ can deduce this by counting the amount of chares (objs). OpenMP counts the amount of iterations.
  Index nPEs = 4; // Charm++ can deduce this by counting the amounf of procssors. OpenMP counts the amount of threads.
}
/**
 * End of the data blocks.
 */

/**
 * OpenMP has no way of tracking the load of a loop-iteration. It must be provided by a user-defined function.
 * The namespace is not necessary.
 */
namespace User {
  Load* loads = new Load[LoadBalancingData::ntasks]();

  void prepare_task_workloads() {
    for(Index i = 0; i < LoadBalancingData::ntasks; ++i)
      loads[i] = i;
  }

  Load* inform_task_workloads() {
    prepare_task_workloads();
    return loads;
  }

  std::string scheduler_selector() {
    return "greedy";
  }
}

int main() {
  /**
   * This block of code is inserted within the RTS.
   * Charm++ has this kind of setup inside the MOGSLibLB;
   * OpenMP has this kind of setup inside the libGOMP functions;
   **/
  MOGSLib::RTS::set_nPEs(LoadBalancingData::nPEs); // Inform the RTS that the machine has 4 processing elements.
  MOGSLib::RTS::set_ntasks(LoadBalancingData::ntasks); // Inform the RTS that th application has 8 work units.
  MOGSLib::RTS::set_task_load_function(User::inform_task_workloads); // Inform the RTS that the task workloads are defined by the user-function "get_loads".
  MOGSLib::SchedulerCollection::pick_scheduler = User::scheduler_selector; // Inform MOGSLib that the function to chose a scheduler is this rather than reading from the ENV.
  /**
   * End of the inside-RTS block.
  **/

  User::prepare_task_workloads(); // This doesnt affect MOGSLib behaviour and is used just for the next prints
  for(decltype(LoadBalancingData::ntasks) i = 0; i < LoadBalancingData::ntasks; ++i)
    std::cout << "Task[" << i << "] has load: " << User::loads[i] << std::endl;

  // The main call for the MOGSLib. This is done inside Charm++ Loadbalancer and inside the mogslib.cpp that needs to be compiled alongside an OpenMP program that uses MOGSLib.
  Index *map = MOGSLib::SchedulerCollection::schedule(); // Pick the scheduler based on the name issued by pick_scheduler, initialize its concepts based on the RTS data and execute the policy.
  std::cout << std::endl << "--- MOGSLib Schedule has been called ---" << std::endl;
  // This is how we interpret the data in the map variable

  Load *PE_total_load = new Load[LoadBalancingData::nPEs]();

  std::cout << std::endl;
  for(decltype(LoadBalancingData::ntasks) i = 0; i < LoadBalancingData::ntasks; ++i) {
    std::cout << "Task " << i << " is mapped to PE " << map[i] << std::endl;
    PE_total_load[map[i]] += User::loads[i];
  }
  
  std::cout << std::endl;

  for(decltype(LoadBalancingData::nPEs) i = 0; i < LoadBalancingData::nPEs; ++i)
    std::cout << "PE " << i << " load is: " << PE_total_load[i] << std::endl;

  return 0;
}