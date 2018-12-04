#pragma once

#include "functionalities.ipp"

namespace MOGSLib { namespace RTS {

template<typename T>
decltype(Charm<T>::stats) Charm<T>::stats = nullptr;
template<typename T>
std::vector<typename T::Index> Charm<T>::chare_ids = std::vector<typename T::Index> {};
template<typename T>
std::vector<typename T::Index> Charm<T>::pu_ids = std::vector<typename T::Index>{};

template<typename T>
typename Charm<T>::Index Charm<T>::LBDB::PU::count() {
  auto &ids = pu_ids;
  ids.clear();

  Charm<T>::LBDB::Helper::filter_unavailable_pus(stats, ids, typename T::UnavailablePUs {});

  return ids.size();
}

template<typename T>
typename Charm<T>::Index Charm<T>::LBDB::Chare::count() {
  auto &ids = chare_ids;
  ids.clear();

  Charm<T>::LBDB::Helper::filter_unmigratable_chares(stats, ids, typename T::FixedChares {});

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
  auto fixed_loads = Charm<T>::LBDB::Helper::loads_from_fixed_chares(stats, typename T::FixedChares {});
  Charm<T>::LBDB::Helper::apply_fixed_chares_load(stats, loads, fixed_loads, typename T::UnavailablePUs {});

  // The PU workload is normalized to account for its pe_speed.
  for(decltype(loads.size()) i = 0; i < loads.size(); ++i)
    loads[i] *= stats->procs[pu_ids[i]].pe_speed;

  return loads;
}

}}