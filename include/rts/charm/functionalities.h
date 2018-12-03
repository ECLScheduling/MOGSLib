#pragma once

namespace MOGSLib { namespace RTS {

/**
 *  @class CharmHelper
 *  @brief A wrapper structure to implement the Charm++'s trait-sensitive functionalities.
 */
struct CharmHelper {
  using LDStats = BaseLB::LDStats*;

  /// @brief Get the amount of PUs in the Charm++ system filtering out the unavailable PUs.
  template<typename I, bool AA>
  static void filter_unavailable_pus(std::vector<I> &ids, LDStats stats);

  /// @brief Get the amount of chares in the Charm++ system filtering out the unmigratable chares.
  template<typename I, bool MA>
  static void filter_unmigratable_chares(std::vector<I> &ids, LDStats stats);

  /// @brief Calculate the loads of fixed chares and add them to host pus.
  template<typename I, typename L, bool AA, bool MA>
  static void add_load_from_fixed_chares(CharmHelper::LDStats stats, std::vector<L> &loads);

  /// @brief Commit the load addition of fixed chares into the host pus.
  template<typename I, typename L, bool AA>
  static void apply_fixed_chares_load(CharmHelper::LDStats stats, std::vector<L>& loads, std::vector<std::pair<I, L>> &fixed_chares);
};

template<typename I, bool AA>
void CharmHelper::filter_unavailable_pus(std::vector<I> &ids, CharmHelper::LDStats stats) {
  auto npus = stats->nprocs();
  for(decltype(npus) i = 0; i < npus; ++i)
    if(stats->procs[i].available)
      ids.push_back(i);
}

template<typename I>
void CharmHelper::filter_unavailable_pus<I, false>(std::vector<I> &ids, CharmHelper::LDStats stats) {
  auto npus = stats->nprocs();
  for(decltype(npus) i = 0; i < npus; ++i)
    ids.push_back(i);
}

template<typename I, bool MA>
void CharmHelper::filter_unmigratable_chares(std::vector<I> &ids, CharmHelper::LDStats stats) {
  auto nchares = stats->n_objs;
  for(auto i = 0; i < nchares; ++i)
    if(stats->objData[i].migratable)
      ids.push_back(i);
}

template<typename I>
void CharmHelper::filter_unmigratable_chares<I, false>(std::vector<I> &ids, CharmHelper::LDStats stats) {
  auto nchares = stats->n_objs;
  for(auto i = 0; i < nchares; ++i)
    ids.push_back(i);
}

template<typename I, typename L, bool AA>
void CharmHelper::apply_fixed_chares_load(CharmHelper::LDStats stats, std::vector<L>& loads, std::vector<std::pair<I, L>> &fixed_chares) {
  for(auto chare : fixed_chares) // All the processors are available, the Charm++ id and MOGSLib id are the same.
    loads[std::get<0>(chare)] += std::get<1>(chare);
}

template<typename I, typename L>
void CharmHelper::apply_fixed_chares_load<I, L, true>(CharmHelper::LDStats stats, std::vector<L>& loads, std::vector<std::pair<I, L>> &fixed_chares) {
  
  // If the system have not detected unavailable pus, call the solution that is not aware of unavailable pus.
  if(CharmDef::pu_ids.size() == stats->nprocs()) {
    apply_fixed_chares_load<I, L, false>(loads, fixed_chares);
    return;
  }

  auto map = new int[stats->nprocs()]();

  // map represents the MOGSLib id
  int i = 0;
  for(decltype(stats->nprocs()) pu = 0; pu < stats->nprocs(); ++pu)
    if(stats->procs[pu].available)
      map[pu] = i++;
    else
      map[pu] = -1;

  for(auto chare : fixed_chares)
    loads[map[std::get<0>(chare)]] += std::get<1>(chare); 

  delete [] map;
}

template<typename I, typename L, bool AA, bool MA>
void CharmHelper::add_load_from_fixed_chares(CharmHelper::LDStats stats, std::vector<L>& loads) {}

template<typename I, typename L, bool AA>
void CharmHelper::add_load_from_fixed_chares<I, L, AA, true>(CharmHelper::LDStats stats, std::vector<L>& loads) {
  std::vector<std::pair<I, L>> fixed_chares;

  for(auto chare = 0; chare < stats->n_objs; ++chare) {
    auto task_data = stats->objData[chare];
    if(!task_data.migratable)
      fixed_chares.push_back(std::make_pair(stats->from_proc[chare], task_data.wallTime));
  }

  if(fixed_chares.size()) // There were at least one fixed tasks.
    apply_fixed_chares_load<I, L, AA>(loads, fixed_chares);
}

}}