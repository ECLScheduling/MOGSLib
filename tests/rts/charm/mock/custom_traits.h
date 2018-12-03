#pragma once

#include "LDStats.h"
#include <rts/charm/traits.ipp>

/**
 * \brief Charm++ custom traits for testing purposes
 */
template<bool check_unavail_pu = true, bool check_fixed_chares = true>
struct CustomCharmTraits : public MOGSLib::CharmBaseTraits {
  static constexpr auto check_for_unavailable_pus = check_unavail_pu;
  static constexpr auto check_for_fixed_chares = check_fixed_chares;
};