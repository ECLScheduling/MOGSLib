#pragma once

#include "traits.h"

namespace MOGSLib { namespace RTS {

/**
 *  @class CharmFunctionalities
 *  @brief A wrapper structure to implement the Charm++'s trait-sensitive functionalities.
 */
template<typename I, typename L>
struct CharmFunctionalities {
  using LDStats = BaseLB::LDStats*;

  /**
   *  @brief Get the amount of PUs in the Charm++ system filtering out the unavailable PUs.
   *  @param ids A vector of ids to add the PU ids.
   *  @param tag A tag used in the tag-dispatch technique to aid the compiler to identify which function will be called.
   *
   *  Add each PU id from the lbdb list in Charm++ filtering out the unavailable ones.
   */
  static void filter_unavailable_pus(LDStats stats, std::vector<I> &ids, CharmSemantics::UnavailablePUs<true> tag);

  /**
   *  @brief Get the amount of PUs in the Charm++ system regardless of the availability status.
   *  @param ids A vector of ids to add the PU ids.
   *  @param tag A tag used in the tag-dispatch technique to aid the compiler to identify which function will be called.
   *
   *  Add each PU id from the lbdb list in Charm++ without any form of label checking.
   */
  static void filter_unavailable_pus(LDStats stats, std::vector<I> &ids, CharmSemantics::UnavailablePUs<false> tag);

  /**
   *  @brief Get the amount of chares in the Charm++ system filtering out the unmigratable chares.
   *  @param ids A vector of ids to add the chare ids.
   *  @param tag A tag used in the tag-dispatch technique to aid the compiler to identify which function will be called.
   *
   *  Add each chare id from the lbdb list in Charm++ filtering out the unmigratable ones.
   */
  static void filter_unmigratable_chares(LDStats stats, std::vector<I> &ids, CharmSemantics::FixedChares<true> tag);

  /**
   *  @brief Get the amount of chares in the Charm++ system regardless of migratability status.
   *  @param ids A vector of ids to add the chare ids.
   *  @param tag A tag used in the tag-dispatch technique to aid the compiler to identify which function will be called.
   *
   *  Add each chare id from the lbdb list in Charm++ without any form of label checking.
   */
  static void filter_unmigratable_chares(LDStats stats, std::vector<I> &ids, CharmSemantics::FixedChares<false> tag);

  /**
   *  @brief Commit the load addition of fixed chares into the host pus.
   *  @param loads A pre-filled vector of PU loads.
   *  @param fixed_chares A vector of pairs containing a fixed chare's host PU id and its load respectively.
   *  @param tag A tag used in the tag-dispatch technique to aid the compiler to identify which function will be called.
   *
   *  MOGSLib filters unavailable PUs to avoid complex schedulers, but Charm++ keeps them, creating different indexes between libraries.
   *  When unavailable PUs might be present, this function should be evoked when applying the load of fixed chares to PUs.
   *  This implementation builds a map to correlate MOGSLib and Charm++ ids to correctly assign the chare loads by id.
   */
  static void apply_fixed_chares_load(LDStats stats, std::vector<L>& loads, std::vector<std::pair<I, L>> &fixed_chares, CharmSemantics::UnavailablePUs<true> tag);

  /**
   *  @brief Commit the load addition of fixed chares into the host pus.
   *  @param loads A pre-filled vector of PU loads.
   *  @param fixed_chares A vector of pairs containing a fixed chare's host PU id and its load respectively.
   *  @param tag A tag used in the tag-dispatch technique to aid the compiler to identify which function will be called.
   *
   *  MOGSLib filters unavailable PUs to avoid complex schedulers, but Charm++ keeps them, creating different indexes between libraries.
   *  When unavailable PUs are not present, this function should be evoked when applying the load of fixed chares to PUs.
   *  This implementation assumes that all processors are available and both MOGSLib and Charm++ PU indices are equal.
   *  This version is more performatic and should be called even when there might be unavailable PUs but none were detected.
   */
  static void apply_fixed_chares_load(LDStats stats, std::vector<L>& loads, std::vector<std::pair<I, L>> &fixed_chares, CharmSemantics::UnavailablePUs<false> tag);

  /**
   *  @brief Fetch the load and the host PU of all the fixed chares.
   *  @param tag A tag used in the tag-dispatch technique to aid the compiler to identify which function will be called.
   *  @return This implementation return an empty vector.
   *
   *  When the tag template value is false, the functionality assumes that there are no fixed chares in the application.
   *  Hence, it returns an empty vector as a result.
   */
  static std::vector<std::pair<I, L>> loads_from_fixed_chares(LDStats stats, CharmSemantics::FixedChares<false> tag);

  /**
   *  @brief Fetch the load and the host PU of all the fixed chares.
   *  @param tag A tag used in the tag-dispatch technique to aid the compiler to identify which function will be called.
   *  @return A vector of pairs, being the first value the fixed chare's host PU id and the second value, its load.
   *
   *  When the tag template value is true, the functionality assumes that there may be fixed chares in the application.
   *  It might return an empty vector, but only if there are no fixed chares in the application.
   */
  static std::vector<std::pair<I, L>> loads_from_fixed_chares(LDStats stats, CharmSemantics::FixedChares<true> tag);
};

}}