#pragma once

#include "LDStats.h"
#include <abstractions/rts/charm/traits.h>

/**
 *  @brief Charm++ custom traits for testing purposes.
 *  This structure let the gtests create different tests for different values of CharmTraits.
 */
template<bool check_unavail_pu = true, bool check_fixed_chares = true>
struct CustomCharmTraits : public MOGSLib::RTS::CharmBaseTraits {
  using UnavailablePUs = MOGSLib::RTS::CharmSemantics::UnavailablePUs<check_unavail_pu>;
  using FixedChares = MOGSLib::RTS::CharmSemantics::FixedChares<check_fixed_chares>;
};