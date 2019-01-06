#pragma once

namespace MOGSLib { namespace RTS {

template<typename I, typename L>
void CharmFunctionalities<I, L>::filter_unavailable_pus(LDStats stats, std::vector<I> &ids, MOGSLib::CharmSemantics::UnavailablePUs<true> tag) {
  auto npus = stats->nprocs();
  for(decltype(npus) i = 0; i < npus; ++i)
    if(stats->procs[i].available)
      ids.push_back(i);
}

template<typename I, typename L>
void CharmFunctionalities<I, L>::filter_unavailable_pus(LDStats stats, std::vector<I> &ids, MOGSLib::CharmSemantics::UnavailablePUs<false> tag) {
  auto npus = stats->nprocs();
  for(decltype(npus) i = 0; i < npus; ++i)
    ids.push_back(i);
}

template<typename I, typename L>
void CharmFunctionalities<I, L>::filter_unmigratable_chares(LDStats stats, std::vector<I> &ids, MOGSLib::CharmSemantics::RigidJobs<true> tag) {
  auto nchares = stats->n_objs;
  for(auto i = 0; i < nchares; ++i)
    if(stats->objData[i].migratable)
      ids.push_back(i);
}

template<typename I, typename L>
void CharmFunctionalities<I, L>::filter_unmigratable_chares(LDStats stats, std::vector<I> &ids, MOGSLib::CharmSemantics::RigidJobs<false> tag) {
  auto nchares = stats->n_objs;
  for(auto i = 0; i < nchares; ++i)
    ids.push_back(i);
}

template<typename I, typename L>
void CharmFunctionalities<I, L>::apply_fixed_chares_load(LDStats stats, std::vector<L>& loads, std::vector<std::pair<I, L>> &fixed_chares, MOGSLib::CharmSemantics::UnavailablePUs<false> tag) {
  for(auto chare : fixed_chares)
    loads[std::get<0>(chare)] += std::get<1>(chare);
}

template<typename I, typename L>
void CharmFunctionalities<I, L>::apply_fixed_chares_load(LDStats stats, std::vector<L>& loads, std::vector<std::pair<I, L>> &fixed_chares, MOGSLib::CharmSemantics::UnavailablePUs<true> tag) {
  if(loads.size() == stats->nprocs()) {
    apply_fixed_chares_load(stats, loads, fixed_chares, MOGSLib::CharmSemantics::UnavailablePUs<false>{});
    return;
  }

  auto map = new int[stats->nprocs()]();

  // map represents the MOGSLib id
  int i = 0;
  for(I pu = 0; pu < stats->nprocs(); ++pu)
    if(stats->procs[pu].available)
      map[pu] = i++;
    else
      map[pu] = -1;

  for(auto chare : fixed_chares)
    loads[map[std::get<0>(chare)]] += std::get<1>(chare); 

  delete [] map;
}

template<typename I, typename L>
std::vector<std::pair<I, L>> CharmFunctionalities<I, L>::loads_from_fixed_chares(LDStats stats, MOGSLib::CharmSemantics::RigidJobs<false> tag) {
  return std::vector<std::pair<I, L>> {};
}

template<typename I, typename L>
std::vector<std::pair<I, L>> CharmFunctionalities<I, L>::loads_from_fixed_chares(LDStats stats, MOGSLib::CharmSemantics::RigidJobs<true> tag) {
  std::vector<std::pair<I, L>> fixed_chares;

  for(auto chare = 0; chare < stats->n_objs; ++chare)
    if(!stats->objData[chare].migratable)
      fixed_chares.push_back(std::make_pair(stats->from_proc[chare], stats->objData[chare].wallTime));
  
  return fixed_chares;
}

}}