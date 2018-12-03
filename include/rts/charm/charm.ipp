#pragma once

#define CHARM_RTS RTS<RuntimeSystemEnum::Charm>

namespace MOGSLib { namespace Abstraction {

decltype(CHARM_RTS::stats) CHARM_RTS::stats = nullptr;
decltype(CHARM_RTS::chare_ids) CHARM_RTS::chare_ids;
decltype(CHARM_RTS::pu_ids) CHARM_RTS::pu_ids;

template<bool Aware>
void CHARM_RTS::LBDB::PU::filter_unavailable(const unsigned &index) {
  if(Charm::stats->procs[index].available)
    Charm::pu_ids.push_back(index);
}

template<>
void CHARM_RTS::LBDB::PU::filter_unavailable<false>(const unsigned &index) {
  Charm::pu_ids.push_back(index);
}

CHARM_RTS::Index CHARM_RTS::LBDB::PU::count() {
  auto npus = Charm::stats->nprocs();

  Charm::pu_ids.clear();
  for(decltype(npus) i = 0; i < npus; ++i)
    filter_unavailable<>(i);

  return Charm::pu_ids.size();
}

template<bool Aware>
void CHARM_RTS::LBDB::Chare::filter_unmigratable(const unsigned &index) {
  if(Charm::stats->objData[index].migratable)
    Charm::chare_ids.push_back(index);
}

template<>
void CHARM_RTS::LBDB::Chare::filter_unmigratable<false>(const unsigned &index) {
  Charm::chare_ids.push_back(index);
}

CHARM_RTS::Index CHARM_RTS::LBDB::Chare::count() {
  auto nchares = Charm::stats->n_objs;

  Charm::chare_ids.clear();
  for(auto i = 0; i < nchares; ++i)
    filter_unmigratable<>(i);

  return Charm::chare_ids.size();
}

std::vector<CHARM_RTS::Load> CHARM_RTS::LBDB::Chare::load_prediction() {
  std::vector<Load> loads;

  for(auto chare : Charm::chare_ids) {
    auto &host_pe = Charm::stats->from_proc[chare];
    auto &pe_speed = Charm::stats->procs[host_pe].pe_speed;

    auto &wall_time = Charm::stats->objData[chare].wallTime;

    loads.push_back(wall_time * pe_speed);
  }

  return loads;
}

template<bool Aware>
void CHARM_RTS::LBDB::PU::apply_fixed_chares_load(std::vector<Load>& loads, std::vector<std::pair<Index, Load>> &fixed_chares) {
  for(auto chare : fixed_chares) // All the processors are available, the Charm++ id and MOGSLib id are the same.
    loads[std::get<0>(chare)] += std::get<1>(chare);
}

template<>
void CHARM_RTS::LBDB::PU::apply_fixed_chares_load<true>(std::vector<Load>& loads, std::vector<std::pair<Index, Load>> &fixed_chares) {
  
  // If the system have not detected unavailable pus, call the solution that is not aware of unavailable pus.
  if(Charm::pu_ids.size() == Charm::stats->nprocs()) {
    apply_fixed_chares_load<false>(loads, fixed_chares);
    return;
  }

  auto map = new int[Charm::stats->nprocs()]();

  // map represents the MOGSLib id
  int i = 0;
  for(decltype(Charm::stats->nprocs()) pu = 0; pu < Charm::stats->nprocs(); ++pu)
    if(Charm::stats->procs[pu].available)
      map[pu] = i++;
    else
      map[pu] = -1;

  for(auto chare : fixed_chares)
    loads[map[std::get<0>(chare)]] += std::get<1>(chare); 

  delete [] map;
}

template<bool Aware>
void CHARM_RTS::LBDB::PU::add_load_from_fixed_chares(std::vector<Load>& loads) {}

template<>
void CHARM_RTS::LBDB::PU::add_load_from_fixed_chares<true>(std::vector<Load>& loads) {
  std::vector<std::pair<Index, Load>> fixed_chares;

  for(auto chare = 0; chare < Charm::stats->n_objs; ++chare) {
    auto task_data = Charm::stats->objData[chare];
    if(!task_data.migratable)
      fixed_chares.push_back(std::make_pair(Charm::stats->from_proc[chare], task_data.wallTime));
  }

  if(!fixed_chares.size()) // There were no fixed tasks.
    return;
  apply_fixed_chares_load<>(loads, fixed_chares);
}

std::vector<CHARM_RTS::Load> CHARM_RTS::LBDB::PU::load_prediction() {
  std::vector<Load> loads;
  
  for(auto pu : Charm::pu_ids)
    loads.push_back(Charm::stats->procs[pu].bg_walltime); // The PU workload prediction is the background walltime.
  add_load_from_fixed_chares<>(loads); // The PU workload prediction is summed to the workload of unmigratable tasks fixed in it.
  
  for(decltype(loads.size()) i = 0; i < loads.size(); ++i)
    loads[i] *= Charm::stats->procs[Charm::pu_ids[i]].pe_speed; // The PU workload is normalized to account for its pe_speed.

  return loads;
}

}}