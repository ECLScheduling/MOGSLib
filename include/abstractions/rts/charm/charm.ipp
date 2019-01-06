#pragma once

#include "functionalities.ipp"

namespace MOGSLib { namespace RTS {

decltype(Charm::stats) Charm::stats = nullptr;
std::vector<typename Charm::Id> Charm::chare_ids = std::vector<typename Charm::Id> {};
std::vector<typename Charm::Id> Charm::pu_ids = std::vector<typename Charm::Id>{};

typename Charm::Id Charm::LBDB::PU::count() {
  auto &ids = pu_ids;
  ids.clear();

  Charm::LBDB::Helper::filter_unavailable_pus(stats, ids, typename Traits::UnavailablePUs {});

  return ids.size();
}

typename Charm::Id Charm::LBDB::Chare::count() {
  auto &ids = chare_ids;
  ids.clear();

  Charm::LBDB::Helper::filter_unmigratable_chares(stats, ids, typename Traits::RigidJobs {});

  return ids.size();
}

void Charm::LBDB::Chare::load_prediction(std::vector<typename Charm::Load> &loads) {
  loads.resize(chare_ids.size());
  Id i = 0;
  for(auto chare : chare_ids) {
    const auto &host_pe = stats->from_proc[chare];
    const auto &pe_speed = stats->procs[host_pe].pe_speed;
    const auto &wall_time = stats->objData[chare].wallTime;

    loads[i++] = wall_time * pe_speed;
  }
}

void Charm::LBDB::PU::load_prediction(std::vector<typename Charm::Load> &loads) {
  loads.resize(pu_ids.size());
  Id i = 0;
  // The PU workload prediction is the background walltime.
  for(auto pu : pu_ids)
    loads[i++] = stats->procs[pu].bg_walltime;
  
  // The PU workload prediction is summed to the workload of unmigratable tasks fixed in it.
  auto fixed_loads = Charm::LBDB::Helper::loads_from_fixed_chares(stats, typename Traits::RigidJobs {});
  Charm::LBDB::Helper::apply_fixed_chares_load(stats, loads, fixed_loads, typename Traits::UnavailablePUs {});

  // The PU workload is normalized to account for its pe_speed.
  for(decltype(loads.size()) i = 0; i < loads.size(); ++i)
    loads[i] *= stats->procs[pu_ids[i]].pe_speed;
}

}}