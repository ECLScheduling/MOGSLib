#pragma once

#include "functionalities.ipp"

namespace MOGSLib { namespace RTS {

decltype(Charm::stats) Charm::stats = nullptr;
std::vector<typename Charm::Id> Charm::chare_ids = std::vector<typename Charm::Id> {};
std::vector<typename Charm::Id> Charm::pu_ids = std::vector<typename Charm::Id>{};

typename Charm::Id Charm::LBDB::PU::count() {
  auto &ids = pu_ids;
  ids.clear();

  Charm::LBDB::Helper::filter_unavailable_pus(stats, ids, typename T::UnavailablePUs {});

  return ids.size();
}

template<typename T>
typename Charm<T>::Id Charm<T>::LBDB::Chare::count() {
  auto &ids = chare_ids;
  ids.clear();

  Charm<T>::LBDB::Helper::filter_unmigratable_chares(stats, ids, typename T::RigidJobs {});

  return ids.size();
}

template<typename T>
std::vector<typename Charm<T>::Load> Charm<T>::LBDB::Chare::load_prediction() {
  std::vector<Load> loads;

  for(auto chare : chare_ids) {
    const auto &host_pe = stats->from_proc[chare];
    const auto &pe_speed = stats->procs[host_pe].pe_speed;
    const auto &wall_time = stats->objData[chare].wallTime;

    loads.push_back(wall_time * pe_speed);
  }

  return loads;
}

template<typename T>
std::vector<typename Charm<T>::Load> Charm<T>::LBDB::PU::load_prediction() {
  std::vector<Load> loads;
  
  // The PU workload prediction is the background walltime.
  for(auto pu : pu_ids)
    loads.push_back(stats->procs[pu].bg_walltime);
  
  // The PU workload prediction is summed to the workload of unmigratable tasks fixed in it.
  auto fixed_loads = Charm<T>::LBDB::Helper::loads_from_fixed_chares(stats, typename T::RigidJobs {});
  Charm<T>::LBDB::Helper::apply_fixed_chares_load(stats, loads, fixed_loads, typename T::UnavailablePUs {});

  // The PU workload is normalized to account for its pe_speed.
  for(decltype(loads.size()) i = 0; i < loads.size(); ++i)
    loads[i] *= stats->procs[pu_ids[i]].pe_speed;

  return loads;
}

}}